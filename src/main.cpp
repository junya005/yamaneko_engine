#define SDL_MAIN_HANDLED
#include "GameApp.h"

/// <summary>
/// アプリケーションのエントリポイント
/// </summary>
int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	GameApp app;
	return app.Run();
}
