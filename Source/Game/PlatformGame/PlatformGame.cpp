#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"

bool PlatformGame::Initialize()
{
	// load audio
	//kiko::g_audioSystem.AddAudio("Laser", "Laser.wav");
	kiko::g_audioSystem.AddAudio("Soundss", "audio/Pokemon-Theme-Song1.wav");
	//m_scoreText = std::make_unique<kiko::Text>(m_font);
	//m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene/platformscene.json");
	m_scene->Load("scene/tilemap.json");
	//m_scene->GetActorByName("Title")->active = true;
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		//auto actor = INSTANTIATE(Actor, "Crate");
		//actor->transform.position = { kiko::random(kiko::g_renderer.GetWidth()), 100 };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));
	}
		break;
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll(dt);
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else
		{
			m_state = eState::PlayerDead;
		}
		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			//Initialize();
			m_state = eState::StartGame;
		}
		break;
	case PlatformGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll(dt);
			//Initialize();
			m_state = eState::StartGame;
		}
		break;
	default:
		break;
	}

	//m_scoreText->Create(kiko::g_renderer, "Score: " + std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	//m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
