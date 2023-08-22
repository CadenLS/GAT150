#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Enemy : public kiko::Actor
	{
	public:
		Enemy(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }//without it calls the default constructor
		{
			m_firerate = 5.0f;
			m_fireTimer = m_firerate;
		}

		///new
		bool Initialize() override;

		void Update(float dt) override; //dt for delta time
		void OnCollision(Actor* other) override;

	protected:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_firerate = 0;
		float m_fireTimer = 0;

		float m_pointTimer = 0;
		float m_pointTime = 15.0f;

		float m_health = 2.0f;
		float m_damage = 0;
	};
}