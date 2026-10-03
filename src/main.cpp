#define SDL_MAIN_HANDLED
#include "GameApp.h"

#pragma region ゲームロジッククラス（将来拡張用）

/// <summary>
/// プレイヤーのクラス
/// </summary>
class Player {
public:
	Player(Character* character, GLuint texture, const ImVec2& position, const ImVec2& size)
		: m_character(character), m_texture(texture), m_position(position), m_size(size)
	{
	}

	~Player() {
		delete m_character;
	}

	bool CheckAlive() const {
		return current_hp > 0;
	}

	bool CheckManaUse(int mp_cost) const {
		return current_mp >= mp_cost;
	}

	void SetCurrentStatusByCharacterClass() {
		current_hp = m_character->GetStatus().hp;
	}
	
private:
	Character* m_character;
	GLuint m_texture;
	ImVec2 m_position;
	ImVec2 m_size;
	int current_hp = 1;
	int current_mp = 1;
};

#pragma endregion

/// <summary>
/// アプリケーションのエントリポイント
/// </summary>
int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	GameApp app;
	return app.Run();
}