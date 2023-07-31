#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "StarField.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Weapon.h"
#include "Player.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		// turning
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		m_transform.rotation += turnAngle * dt; //turnAngle * 5 * dt make turn faster
		// check to see if enemy can see you
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			// They see me

			// use fire timer to tell when creating a bullet, then reset

				if (m_fireTimer <= 0) {

					kiko::Transform transform { m_transform.position, m_transform.rotation, 1};
					std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
					weapon->m_tag = "EnemyBullet";

					m_scene->Add(std::move(weapon));

					m_fireTimer = m_fireRate;
				}
				else {
					m_fireTimer -= dt;
				}
		}
	}

	if (m_tag == "EnemyB")
	{
		m_pointTimer += dt;
		if (m_pointTimer >= m_pointTime)
		{
			m_pointTimer = 0;
			m_game->AddPoints(200);
		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

}

	void Enemy::OnCollision(Actor* other)
	{
		if (m_tag == "Enemy")
		{
			if (other->m_tag == "PlayerBullet")
			{
				//m_health - m_damage;
				//if (m_health <= 0) m_destroyed = true;
				m_game->AddPoints(100);
				kiko::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 200;
				data.angle = 0;
				data.angleRange = kiko::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMin = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = kiko::Color{ 1, 0, 1, 1 };
				kiko::Transform transform{ { m_transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->m_lifespan = 1.0f;
				m_scene->Add(std::move(emitter));
				m_destroyed = true;
			}
		}
	}