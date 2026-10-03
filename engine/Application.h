#pragma once

#include "Window.h"
#include "Input.h"
#include "AssetManager.h"
#include "Time.h"
#include "Config.h"
#include "Scene.h"
#include "SceneManager.h"

namespace Engine {

	/// <summary>
	/// SDL2、OpenGL、GLAD、ImGuiの初期化・終了処理、および毎フレームのゲームループ実行を一元管理するための抽象基底クラスです。
	/// </summary>
	/// <remarks>
	/// ゲーム側はこのクラスを継承して派生クラス（例: GameApp）を定義し、仮想フック（OnInit, OnUpdate 等）をオーバーライドして固有処理を記述します。
	/// <code>
	/// class MyGameApp : public Engine::Application {
	/// public:
	///     MyGameApp() : Application({ .title = "My Game", .windowWidth = 1280, .windowHeight = 720 }) {}
	/// protected:
	///     bool OnInit() override {
	///         // 初期シーンの設定など
	///         return true;
	///     }
	///     void OnUpdate(float deltaTime) override {
	///         // 毎フレームの更新ロジック
	///     }
	/// };
	/// 
	/// int main(int argc, char* argv[]) {
	///     MyGameApp app;
	///     return app.Run();
	/// }
	/// </code>
	/// </remarks>
	class Application {
	public:
		/// <summary>
		/// アプリケーション初期設定情報を受け取り、インスタンスを構築するために存在します。
		/// </summary>
		/// <param name="config">ウィンドウタイトルや解像度、クリアカラーなどの初期設定データ</param>
		/// <remarks>
		/// <code>
		/// // 派生クラスのメンバ初期化子から設定を注入する例
		/// MyGameApp() : Application({
		///     .title = "Sample Game",
		///     .windowWidth = 1920,
		///     .windowHeight = 1080,
		///     .vsync = true
		/// }) {}
		/// </code>
		/// </remarks>
		explicit Application(const AppConfigData& config = AppConfigData{});

		/// <summary>
		/// アプリケーションインスタンスを破棄し、静的インスタンス参照をクリアします。
		/// </summary>
		/// <remarks>
		/// <code>
		/// // アプリケーション終了時に自動的に破棄されます
		/// </code>
		/// </remarks>
		virtual ~Application();

		/// <summary>
		/// 全サブシステムの初期化を実行し、終了要求（Quit）があるまでメインゲームループを反復駆動するために存在します。
		/// </summary>
		/// <returns>正常終了時は 0、初期化失敗などのエラー時は -1</returns>
		/// <remarks>
		/// <code>
		/// int main(int argc, char* argv[]) {
		///     GameApp app;
		///     return app.Run();
		/// }
		/// </code>
		/// </remarks>
		int Run();

		/// <summary>
		/// 現在実行中のメインゲームループに対して安全な終了フラグをセットするために存在します。
		/// </summary>
		/// <remarks>
		/// <code>
		/// // Escキー押下時や終了ボタン押下時に呼び出す例
		/// if (Engine::Input::GetKeyDown(SDLK_ESCAPE)) {
		///     Engine::Application::Get()->Quit();
		/// }
		/// </code>
		/// </remarks>
		void Quit();

		/// <summary>
		/// 現在実行中の Application インスタンスへのポインタを取得します。
		/// </summary>
		/// <returns>現在有効な Application インスタンス。未生成時は nullptr</returns>
		/// <remarks>
		/// <code>
		/// Engine::Application* app = Engine::Application::Get();
		/// if (app) {
		///     app->Quit();
		/// }
		/// </code>
		/// </remarks>
		static Application* Get() { return s_instance; }

	protected:
		/// <summary>
		/// エンジン初期化完了後、ゲームループ開始直前にゲーム固有の初期化（リソース確保や初期シーン遷移等）を行うための仮想フックです。
		/// </summary>
		/// <returns>初期化に成功した場合は true、失敗してアプリを終了する場合は false</returns>
		/// <remarks>
		/// <code>
		/// bool OnInit() override {
		///     Engine::SceneManager::ChangeScene<TitleScene>();
		///     return true;
		/// }
		/// </code>
		/// </remarks>
		virtual bool OnInit() { return true; }

		/// <summary>
		/// ゲームループ終了後、エンジンリソース破棄直前にゲーム固有の終了処理（解放等）を行うための仮想フックです。
		/// </summary>
		/// <remarks>
		/// <code>
		/// void OnShutdown() override {
		///     // ゲーム固有リソースの解放処理
		/// }
		/// </code>
		/// </remarks>
		virtual void OnShutdown() {}

		/// <summary>
		/// 毎フレームのロジック更新処理を行うための仮想フックです。
		/// </summary>
		/// <param name="deltaTime">前フレームからの経過時間（秒単位）</param>
		/// <remarks>
		/// <code>
		/// void OnUpdate(float deltaTime) override {
		///     // 時間経過に応じたオブジェクト移動や状態監視
		/// }
		/// </code>
		/// </remarks>
		virtual void OnUpdate(float deltaTime) { (void)deltaTime; }

		/// <summary>
		/// 画面クリア直後、ImGui描画前に生OpenGL描画（3Dモデル描画やカスタムシェーダー描画）を行うための仮想フックです。
		/// </summary>
		/// <remarks>
		/// <code>
		/// void OnRender() override {
		///     // OpenGLによる直接メッシュ描画処理
		/// }
		/// </code>
		/// </remarks>
		virtual void OnRender() {}

		/// <summary>
		/// ImGuiのフレーム開始後、ImGui描画発行前にUI要素を構築・描画するための仮想フックです。
		/// </summary>
		/// <remarks>
		/// <code>
		/// void OnImGuiRender() override {
		///     ImGui::Begin("Status Window");
		///     ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		///     ImGui::End();
		/// }
		/// </code>
		/// </remarks>
		virtual void OnImGuiRender() {}

	private:
		/// <summary>低レベルライブラリ群（SDL, OpenGL, GLAD, ImGui）および全サブシステムの初期化を内部実行します。</summary>
		bool Initialize();

		/// <summary>全サブシステムおよびライブラリを適切な逆順で解放・シャットダウンします。</summary>
		void Shutdown();

		/// <summary>起動時にコンストラクタへ渡されたアプリケーション初期設定データ</summary>
		AppConfigData m_initialConfig;

		/// <summary>メインゲームループが継続中かを示す実行制御フラグ</summary>
		bool m_isRunning = false;

		/// <summary>本アプリケーションが所有するメインウィンドウおよびコンテキスト管理インスタンス</summary>
		Window m_window;

		/// <summary>シングルトンアクセス用の静的インスタンス参照ポインタ</summary>
		static Application* s_instance;
	};

}
