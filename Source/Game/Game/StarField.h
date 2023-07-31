#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class StarField : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver

	};

public:


	// Inherited via Game
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3.0f;

	float m_bosspawnTr = 0;
	float m_bossspawnT = 15.0f;

	float m_stateTimer = 0;

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_titleText;
	std::unique_ptr<kiko::Text> m_gameoverText;

	std::unique_ptr<kiko::Text> m_oneshotText;
	std::unique_ptr<kiko::Text> m_twoshotText;
	std::unique_ptr<kiko::Text> m_shotgunText;
	std::unique_ptr<kiko::Text> m_lazerText;
};