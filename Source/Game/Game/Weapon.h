#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
    class Weapon : public Actor
    {
    public:
        CLASS_DECLARATION(Weapon)

        bool Initialize() override;
        void Update(float dt) override; //dt for delta time
        void OnCollisionEnter(Actor* other);

    protected:
        float speed = 0;
        float m_turnRate = 0;
        kiko::PhysicsComponent* m_physicsComponent = nullptr;
    };
}