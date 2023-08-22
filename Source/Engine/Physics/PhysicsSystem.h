#pragma once
#include "Framework/Singleton.h"
#include "../ThirdParty/box2d/include/box2d/b2_world.h"
#include <memory>

namespace kiko
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);
		friend class Singelton;

	public:
		PhysicsSystem() = default;
	private:
		std::unique_ptr<b2World> m_world;
	};
}