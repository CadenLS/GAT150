#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		Player(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }//without it calls the default constructor
		{}

		bool Initialize() override;
		void Update(float dt) override; //dt for delta time
		void OnCollision(Actor* other) override;

	protected:
		float m_speed = 0;
		float m_turnRate = 0;
		kiko::vec2 m_dashDirection; // Dash direction vector

		float m_turnrate = 0;
		float m_health = 100.0f;
		float m_damage = 15.0f;

		float m_singleTime = 1.0f;
		float m_doubleTime = 3.0f;

		float m_shotgunTime = 10.0f;
		float m_singleTimer = 0;

		float m_doubleTimer = 0;
		float m_shotgunTimer = 0;

		float m_lazerTimer = 0;
		float m_lazerTime = 15.0f;
		float m_lazerStop = 2.0f;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}