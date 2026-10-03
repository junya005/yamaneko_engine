#pragma once
#include "../engine/Engine.h"

/// <summary>
/// テンプレートゲームのメインアプリケーションクラスです。
/// Engine::Application を継承し、プレイヤーの移動ロジックやUI描画を実装します。
/// </summary>
class GameApp : public Engine::Application {
public:
	GameApp();
	~GameApp() override;

protected:
	bool OnInit() override;
	void OnShutdown() override;
	void OnUpdate(float deltaTime) override;
	void OnImGuiRender() override;

private:
	/// <summary>プレイヤー四角形のX座標（ピクセル単位）</summary>
	float m_playerX = 100.0f;

	/// <summary>プレイヤー四角形のY座標（ピクセル単位）</summary>
	float m_playerY = 100.0f;

	/// <summary>プレイヤーの移動速度（ピクセル/秒）</summary>
	float m_playerSpeed = 300.0f;

	/// <summary>プレイヤー四角形のサイズ（ピクセル単位）</summary>
	float m_playerSize = 50.0f;
};
