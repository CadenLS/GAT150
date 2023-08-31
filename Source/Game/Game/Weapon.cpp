#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(Actor::transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

		Actor::transform.position.x = kiko::Wrap(Actor::transform.position.x, (float)kiko::g_renderer.GetWidth());
		Actor::transform.position.y = kiko::Wrap(Actor::transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollisionEnter(Actor* other)
	{
		if (other->Actor::tag != tag)
		{
			destroyed = true;
		}
	}
	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, m_turnRate);
	}
}
