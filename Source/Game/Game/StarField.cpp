#include "StarField.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"

bool StarField::Initialize()
{
	//m_font = kiko::g_resources.Get<kiko::Font>("QuirkyRobot.ttf", 24);
	m_font = GET_RESOURCE(kiko::Font, "QuirkyRobot.ttf", 24);

	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "STAR FIELD", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_oneshotText = std::make_unique<kiko::Text>(m_font);
	m_oneshotText->Create(kiko::g_renderer, "SINGLE", kiko::Color{ 1, 1, 1, 1 });

	m_twoshotText = std::make_unique<kiko::Text>(m_font);
	m_twoshotText->Create(kiko::g_renderer, "DOUBLE", kiko::Color{ 1, 1, 1, 1 });
	
	m_shotgunText = std::make_unique<kiko::Text>(m_font);
	m_shotgunText->Create(kiko::g_renderer, "SHOTGUN", kiko::Color{ 1, 1, 1, 1 });

	m_lazerText = std::make_unique<kiko::Text>(m_font);
	m_lazerText->Create(kiko::g_renderer, "LAZER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("Laser", "Laser.wav");
	kiko::g_audioSystem.AddAudio("Explode", "Explosion.wav");
	kiko::g_audioSystem.AddAudio("Sound", "beyondf.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene.json");
	m_scene->GetActorByName("Title")->active = true;
	//m_scene->GetActorByName("Title")->active = false;
	m_scene->Initialize();

	return true;
}

void StarField::Shutdown()
{
}

void StarField::Update(float dt)
{
	switch (m_state)
	{
	case StarField::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			//m_scene->GetActorByName("Background")->active = false;
		}
		break;
	case StarField::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case StarField::eState::StartLevel:
		m_scene->RemoveAll(dt);
	{
			//Create Player
			m_scene->RemoveAll(dt);
			auto player = std::make_unique<kiko::Player>(10.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 1 });
			player->tag = "Player";
			player->m_game = this;

			//create Components
			auto renderComponent = CREATE_CLASS(SpriteComponent)
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "Shipss.png", kiko::g_renderer);
			player->AddComponent(std::move(renderComponent));

			//adding physics
			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
			physicsComponent->m_damping = 0.5f;
			player->AddComponent(std::move(physicsComponent));
			
			///newwwww
			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			///VVVVVVV new
			player->Initialize();
			m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case StarField::eState::Game:
		if (m_score <= 1500)
		{
			m_spawnTimer += dt;
			if(m_spawnTimer >= m_spawnTime)
			{
				m_spawnTimer = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3 });
				enemy->tag = "Enemy";
				enemy->m_game = this;
				// create components
				//---------------------------------------Put the enemy pngs instead
				auto component = kiko::Factory::Instance().Create<kiko::SpriteComponent>("SpriteComponent");
				component->m_texture = GET_RESOURCE(kiko::Texture, "Shipss.png", kiko::g_renderer);
				enemy->AddComponent(std::move(component));

				///newwwww add to each enemy you have
				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}

			m_bosspawnTr += dt;
			if (m_bosspawnTr >= m_bossspawnT)
			{
				m_bosspawnTr = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 6 });
				enemy->tag = "EnemyB";
				enemy->m_game = this;
				// create components
				//---------------------------------------Put the enemy pngs instead
				auto component = kiko::Factory::Instance().Create<kiko::SpriteComponent>("SpriteComponent");
				component->m_texture = GET_RESOURCE(kiko::Texture, "Shipss.png", kiko::g_renderer);
				enemy->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}
		}

		if (m_score > 1500)
		{
			m_spawnTimer += dt;
			if (m_spawnTimer >= m_spawnTime)
			{
				m_spawnTimer = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3 });
				enemy->tag = "Enemy";
				enemy->m_game = this;

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}

			m_bosspawnTr += dt;
			if (m_bosspawnTr >= m_bossspawnT)
			{
				m_bosspawnTr = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 6 });
				enemy->tag = "EnemyB";
				enemy->m_game = this;

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}
			m_spawnTimer += dt;
			if (m_spawnTimer >= m_spawnTime)
			{
				m_spawnTimer = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3 });
				enemy->tag = "Enemy";
				enemy->m_game = this;

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}

			m_bosspawnTr += dt;
			if (m_bosspawnTr >= m_bossspawnT)
			{
				m_bosspawnTr = 0;
				std::unique_ptr<kiko::Enemy> enemy = std::make_unique<kiko::Enemy>(75.0f, kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 6 });
				enemy->tag = "EnemyB";
				enemy->m_game = this;

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				enemy->AddComponent(std::move(collisionComponent));

				enemy->Initialize();
				m_scene->Add(std::move(enemy));
			}
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else
		{ 
			m_state = eState::PlayerDead;
			kiko::g_audioSystem.PlayOneShot("Explode");

		}
		break;
	case StarField::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case StarField::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll(dt);
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, "Score: " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void StarField::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);

	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_J))
	{
		m_oneshotText->Draw(renderer, 600, 40);
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_K))
	{
		m_twoshotText->Draw(renderer, 600, 40);
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_L))
	{
		m_shotgunText->Draw(renderer, 600, 40);
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_M))
	{
		m_lazerText->Draw(renderer, 600, 40);
	}

	m_scoreText->Draw(renderer, 40, 40);
	kiko::g_particleSystem.Draw(renderer);
}
