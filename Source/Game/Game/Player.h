#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnrate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
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
};