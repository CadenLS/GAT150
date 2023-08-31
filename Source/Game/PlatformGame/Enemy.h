#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		bool Initialize() override;
		void Update(float dt) override; //dt for delta time
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	protected:
		float speed = 0;
		int groundCount = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};
}