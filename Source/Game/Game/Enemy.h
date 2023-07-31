#pragma once
#include "Framework/Actor.h"

class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnrate{ turnRate }
	{
		m_fireRate = 5.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnrate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;

	float m_pointTimer = 0;
	float m_pointTime = 15.0f;

	float m_health = 2.0f;
	float m_damage = 0;
};