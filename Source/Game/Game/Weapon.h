#pragma once
#include "Framework/Actor.h"

namespace kiko
{
    class Weapon : public Actor
    {
    public:
        CLASS_DECLARATION(Weapon)

        bool Initialize() override;
        void Update(float dt) override; //dt for delta time
        void OnCollision(Actor* other);

    protected:
        float speed = 0;
        float m_turnRate = 0;
    };
}