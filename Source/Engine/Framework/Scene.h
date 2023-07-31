#pragma once
#include "Actor.h"

#include <list>
//unity calls these scenes too

namespace kiko
{
    //forward declaration - tells the compiler that it doesnt need to know shit bout the renderer's reference
        //doesnt work with functions, can only declare variables
    class Renderer;

    class Scene
    {
    public:
        Scene() = default;

        void Update(float dt);
        void Draw(Renderer& renderer);

        void Add(std::unique_ptr<Actor> actor);
        void RemoveAll();

        template<typename T>
        T* GetActor();

        friend class Actor;

    private:
        std::list<std::unique_ptr<Actor>> m_actors; //contains POINTER of actors, more optimal for constantly changing
    };

    template<typename T>
    inline T* Scene::GetActor()
    {
        for (auto& actor : m_actors)
        {
            T* result = dynamic_cast<T*>(actor.get());
            if (result) return result;
        }

        return nullptr;
    }
}