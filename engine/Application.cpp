#include "Application.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application(const AppConfigData& config) : m_initialConfig(config) {
		s_instance = this;
	}

	Application::~Application() {
		if (s_instance == this) {
			s_instance = nullptr;
		}
	}

	void Application::Quit() {
		m_isRunning = false;
	}

	bool Application::Initialize() {
		// 設定の初期化
		Config::Initialize(m_initialConfig);
		const auto& config = Config::Get();

		// SDLの初期化
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// OpenGLの属性設定
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// ウィンドウとOpenGL/GLADの初期化
		if (!m_window.Initialize(config.title, config.windowWidth, config.windowHeight, SDL_WINDOW_OPENGL, config.vsync)) {
			SDL_Log("Failed to initialize Window");
			return false;
		}

		// サブシステムの初期化
		Time::Initialize();
		Input::Initialize();
		AssetManager::Initialize();
		SceneManager::Initialize();

		// ImGuiの初期化（標準フォントで初期化）
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		// ImGuiバックエンドの初期化
		ImGui_ImplSDL2_InitForOpenGL(m_window.GetSDLWindow(), m_window.GetGLContext());
		ImGui_ImplOpenGL3_Init("#version 150");

		// 派生クラスの初期化フック呼び出し（ゲーム固有フォント追加やシーン設定等）
		if (!OnInit()) {
			SDL_Log("Failed to initialize game application (OnInit returned false)");
			return false;
		}

		m_isRunning = true;
		return true;
	}

	void Application::Shutdown() {
		// 派生クラスの終了処理フック
		OnShutdown();

		// シーンマネージャーの終了
		SceneManager::Shutdown();

		// ImGuiの終了処理
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		// 各サブシステムの解放
		AssetManager::Shutdown();
		m_window.Cleanup();

		// SDLの終了
		SDL_Quit();
	}

	int Application::Run() {
		if (!Initialize()) {
			Shutdown();
			return -1;
		}

		while (m_isRunning) {
			// 1. イベントポーリング
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					m_isRunning = false;
				}
				ImGui_ImplSDL2_ProcessEvent(&e);
				Input::OnProcessEvent(e);
			}

			// 2. 時間更新
			Time::Update();
			float deltaTime = Time::GetDeltaTime();

			// 3. 入力フレーム開始
			Input::OnBeginFrame();

			// 4. ロジック更新
			OnUpdate(deltaTime);
			SceneManager::Update(deltaTime);

			// 5. 画面クリア
			const auto& clearColor = Config::Get().clearColor;
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// 6. 生OpenGL描画
			OnRender();
			SceneManager::Render();

			// 7. ImGuiフレーム開始
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			// 8. ImGui UI描画
			OnImGuiRender();
			SceneManager::OnImGuiRender();

			// 9. ImGui描画発行
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// 10. バッファスワップ
			m_window.SwapBuffers();
		}

		Shutdown();
		return 0;
	}

}
