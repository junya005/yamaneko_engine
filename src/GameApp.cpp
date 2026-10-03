#include "GameApp.h"
#include <imgui.h>
#include <algorithm>

GameApp::GameApp() : Engine::Application({
	.title = "Template Game",
	.windowWidth = 1280,
	.windowHeight = 720,
	.vsync = true,
	.clearColor = { 0.1f, 0.12f, 0.15f, 1.0f }
}) {

}

GameApp::~GameApp() {

}

bool GameApp::OnInit() {
	// 初期位置の設定
	m_playerX = 100.0f;
	m_playerY = 100.0f;
	return true;
}

void GameApp::OnShutdown() {

}

void GameApp::OnUpdate(float deltaTime) {
	float moveDistance = m_playerSpeed * deltaTime;

	// WASDキー入力による移動
	if (Engine::Input::GetKey(SDL_SCANCODE_W)) {
		m_playerY -= moveDistance;
	}
	if (Engine::Input::GetKey(SDL_SCANCODE_S)) {
		m_playerY += moveDistance;
	}
	if (Engine::Input::GetKey(SDL_SCANCODE_A)) {
		m_playerX -= moveDistance;
	}
	if (Engine::Input::GetKey(SDL_SCANCODE_D)) {
		m_playerX += moveDistance;
	}

	// 画面外への飛び出し防止（クランプ処理）
	int screenWidth = Engine::Window::Width();
	int screenHeight = Engine::Window::Height();
	if (screenWidth > 0 && screenHeight > 0) {
		m_playerX = std::clamp(m_playerX, 0.0f, static_cast<float>(screenWidth) - m_playerSize);
		m_playerY = std::clamp(m_playerY, 0.0f, static_cast<float>(screenHeight) - m_playerSize);
	}
}

void GameApp::OnImGuiRender() {
	// 1. プレイヤー四角形の描画（ImGui BackgroundDrawList）
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImVec2 pMin(m_playerX, m_playerY);
	ImVec2 pMax(m_playerX + m_playerSize, m_playerY + m_playerSize);
	drawList->AddRectFilled(pMin, pMax, IM_COL32(255, 255, 255, 255));
	drawList->AddRect(pMin, pMax, IM_COL32(100, 200, 255, 255), 0.0f, 0, 2.0f);

	// 2. デバッグ・操作情報ウィンドウの描画
	ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(320.0f, 220.0f), ImGuiCond_Once);

	if (ImGui::Begin("Template Controller & Debug")) {
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "[Controls]");
		ImGui::BulletText("W / A / S / D : Move Square");

		ImGui::Separator();
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "[Performance]");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("DeltaTime: %.4f s", Engine::Time::GetDeltaTime());
		ImGui::Text("TotalTime: %.1f s", Engine::Time::GetTotalTime());

		ImGui::Separator();
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "[Player Info]");
		ImGui::Text("Position: (%.1f, %.1f)", m_playerX, m_playerY);
		ImGui::SliderFloat("Speed", &m_playerSpeed, 100.0f, 1000.0f);

		if (ImGui::Button("Reset Position")) {
			m_playerX = 100.0f;
			m_playerY = 100.0f;
		}
	}
	ImGui::End();
}
