#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "../engine/Engine.h"

// プロダクト名
const char PRODUCT_NAME[] = "My Product";

// ウィンドウサイズ
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

/// <summary>
/// メイン関数
/// </summary>
int main(int argc, char* argv[]) {  
	// SDLの初期化
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Failed to initialization.: %s", SDL_GetError());
		return -1;
	}

	// ウィンドウの初期化
	Engine::Window window;
	if (!window.Initialize(PRODUCT_NAME, WINDOW_WIDTH, WINDOW_HEIGHT)) {
		return -1;
	}

	// レンダラーの初期化
	Engine::Renderer renderer;
	if (!renderer.Initialize(window.GetSDLWindow())) {
		return -1;
	}

	// 入力の初期化
	Engine::Input input;

	// プレイヤーの座標
	int x = 50, y = 50;

	// 終了要求フラグ
	bool is_request_quit = false;

	// メインループ
	while (!is_request_quit)
	{
		// イベント処理
		SDL_Event e = {};
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				is_request_quit = true;
			}
			else {
				input.ProcessEvent(e);
			}
		}

		// 状態更新処理
		// キー入力によるプレイヤー座標の更新
		if (input.GetKey(SDL_SCANCODE_W)) {
			y--;
		}	
		if (input.GetKey(SDL_SCANCODE_S)) {
			y++;
		}	
		if (input.GetKey(SDL_SCANCODE_A)) {
			x--;
		}
		if (input.GetKey(SDL_SCANCODE_D)) {
			x++;
		}

		// 描画処理
		// 画面のクリア
		renderer.Clear(0, 0, 0, 255);

		// プレイヤーの描画
		renderer.SetRendererDrawColor(255, 255, 255, 255);
		SDL_Rect rect = { x,y, 50, 50 };
		renderer.DrawRect(rect);

		// 画面の更新
		renderer.Present();
	}

	SDL_Quit();
	return 0;
}