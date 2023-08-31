#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		// movement
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		bool onGround = (groundCount > -1);
		vec2 velocity = m_physicsComponent->m_velocity;
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -0.1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 0.1;

		//animation
		if (std::fabs(velocity.x) > 0.2f && tag == "EnemyB")
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("walkW");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idleEx");
		}
		if (std::fabs(velocity.x) > 0.2f && tag == "EnemyG")
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("walkWe");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idleExx");
		}
		if (std::fabs(velocity.x) > 0.2f && tag == "Enemy")
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir > 0);
			m_spriteAnimComponent->SetSequence("idleE");
		}
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			//kiko::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
			//destroyed = true;
		}
		if (tag == "Coin")
		{
			m_game->AddPoints(200);
		}

	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
	}
}
