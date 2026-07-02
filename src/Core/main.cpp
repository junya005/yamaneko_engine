#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

// プロダクト名
const char PRODUCT_NAME[] = "My Product";

// ウィンドウサイズ
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// インスタンス
static SDL_Window* windowInstance = nullptr;
static SDL_Renderer* rendererInstance = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int main(int argc, char* argv[]) {    

	// プレイヤーの座標
	int x = 50, y = 50;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("%s", "Failed to initialization.");
		return -1;
	}

	windowInstance = SDL_CreateWindow(PRODUCT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (windowInstance == nullptr) {
		SDL_Log("ウィンドウの初期化に失敗しました。: %s", SDL_GetError());
		return -1;
	}

	rendererInstance = SDL_CreateRenderer(windowInstance, 0, SDL_RENDERER_ACCELERATED);
	if (rendererInstance == nullptr){
		SDL_Log("レンダラーの初期化に失敗しました: %s", SDL_GetError());
		return -1;
	}

	while (true)
	{
		SDL_Event e = {};
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		const Uint8* keyboardStats = SDL_GetKeyboardState(NULL);
		if (keyboardStats[SDL_SCANCODE_W]) {
			y--;
		}	
		if (keyboardStats[SDL_SCANCODE_S]) {
			y++;
		}	
		if (keyboardStats[SDL_SCANCODE_A]) {
			x--;
		}
		if (keyboardStats[SDL_SCANCODE_D]) {
			x++;
		}

		SDL_SetRenderDrawColor(rendererInstance, 0, 0, 0, 0xFF);
		SDL_RenderClear(rendererInstance);

		SDL_SetRenderDrawColor(rendererInstance, 0xFF, 0, 0, 0xFF);
		SDL_Rect rect = { x,y, 50, 50 };
		SDL_RenderFillRect(rendererInstance, &rect);
		SDL_RenderPresent(rendererInstance);

		
	}

	if (rendererInstance) {
		SDL_DestroyRenderer(rendererInstance);
		rendererInstance = nullptr;
	}

	if (windowInstance) {
		SDL_DestroyWindow(windowInstance);
		windowInstance = nullptr;
	}

	SDL_Quit();
	return 0;
}