#include "Player.h"
#include "Input/InputSystem.h"
#include "StarField.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Weapon.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	//kiko::g_audioSystem.Initialize();
	//kiko::g_audioSystem.Update();

	// movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnrate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);
	//m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire single weapon
	m_singleTimer += dt;
	if (m_singleTimer >= m_singleTime)
	{
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_J))
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			{
				// create weapon
				kiko::g_audioSystem.PlayOneShot("Laser");
				kiko::Transform transform1{ m_transform.position, m_transform.rotation, 1.0f };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				// Reset the timer
				m_singleTimer = 0;
			}
		}
	}

	// fire double weapon
	m_doubleTimer += dt;
	if (m_doubleTimer >= m_doubleTime)
	{
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_K))
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			{
				kiko::g_audioSystem.PlayOneShot("Laser");
				// create weapon
				kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1.0f };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				// Makes two bullets
				kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), 1.0f };
				weapon = std::make_unique<Weapon>(400.0f, transform2, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				m_doubleTimer = 0;
			}
		}
	}

	// fire shotgun weapon
	m_shotgunTimer += dt;
	if (m_shotgunTimer >= m_shotgunTime)
	{
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_L))
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			{
				kiko::g_audioSystem.PlayOneShot("Laser");
				kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(kiko::randomf(20.0f)), 0.5f };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(kiko::randomf(20.0f)), 0.5f };
				weapon = std::make_unique<Weapon>(400.0f, transform2, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				kiko::Transform transform3{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(kiko::randomf(20.0f)), 0.5f };
				weapon = std::make_unique<Weapon>(400.0f, transform3, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				kiko::Transform transform4{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(kiko::randomf(20.0f)), 0.5f };
				weapon = std::make_unique<Weapon>(400.0f, transform4, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				kiko::Transform transform5{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(kiko::randomf(20.0f)), 0.5f };
				weapon = std::make_unique<Weapon>(400.0f, transform5, m_model);
				weapon->m_tag = "PlayerBullet";
				m_scene->Add(std::move(weapon));

				m_shotgunTimer = 0;
			}
		}
	}

	// fire lazerrrr
	m_lazerTimer += dt;
	if (m_lazerTimer >= m_lazerTime)
	{
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_M))
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				if (m_lazerStop >= 0)
				{
					m_lazerStop -= dt;
					kiko::Transform transform1{ m_transform.position, m_transform.rotation, 0.5f };
					std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, m_model);
					weapon->m_tag = "PlayerBullet";
					m_scene->Add(std::move(weapon));

					if (m_lazerStop < 0)
					{
						m_lazerStop = 1.0f;
						m_lazerTimer = 0;
					}
				}
			}
		}
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "EnemyBullet")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<StarField*>(m_game)->SetState(StarField::eState::PlayerDeadStart);
		//m_health - m_damage;
		//if (m_health <= 0) m_destroyed = true;
		m_destroyed = true;
	}

	if (other->m_tag == "EnemyB")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<StarField*>(m_game)->SetState(StarField::eState::PlayerDeadStart);
		m_destroyed = true;
	}
}
