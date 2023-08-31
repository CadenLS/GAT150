#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "StarField.h"
#include "Framework/Framework.h"
#include "Weapon.h"
#include "Player.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)
	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::Vector2 direction = player->transform.position - transform.position;
			// turning
			float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
			//transform.rotation += turnAngle * dt; //turnAngle * 5 * dt make turn faster
			m_physicsComponent->ApplyTorque(turnAngle);
			// check to see if enemy can see you
			if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
			{
				// They see me
				// use fire timer to tell when creating a bullet, then reset

				if (m_fireTimer <= 0) {

					auto weapon = INSTANTIATE(Weapon, "Rocket");
					weapon->transform = { transform.position, transform.rotation, 1.0f };
					weapon->Initialize();
					m_scene->Add(std::move(weapon));

					m_fireTimer = m_firerate;
				}
				else {
					m_fireTimer -= dt;
				}
			}
		}

		if (tag == "EnemyB")
		{
			m_pointTimer += dt;
			if (m_pointTimer >= m_pointTime)
			{
				m_pointTimer = 0;
				m_game->AddPoints(200);
			}
		}

		transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (tag == "Enemy")
		{
			if (other->tag == "PlayerBullet")
			{
				//m_health - m_damage;
				//if (m_health <= 0) m_destroyed = true;
				//m_game->AddPoints(100);
				kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
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

				kiko::Transform transform{ { this->transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->lifespan = 1.0f;
				m_scene->Add(std::move(emitter));
				destroyed = true;
			}
		}
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, m_speed);
		READ_DATA(value, m_turnRate);
		READ_DATA(value, m_fireTimer);
		READ_DATA(value, m_pointTimer);
	}
}