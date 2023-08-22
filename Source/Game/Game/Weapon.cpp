#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = Actor::transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(Actor::transform.rotation);
		Actor::transform.position += forward * speed * kiko::g_time.GetDeltaTime();

		Actor::transform.position.x = kiko::Wrap(Actor::transform.position.x, (float)kiko::g_renderer.GetWidth());
		Actor::transform.position.y = kiko::Wrap(Actor::transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(Actor* other)
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
	}
}
