#pragma once

namespace kiko
{
    template <typename T> //makes the entire class a typename T, like a parent class but different
    class Singleton
    {
    public:
        Singleton(const Singleton& other) = delete; //copy operator - makes a copy of b and makes it a //delete = no one can copy
        Singleton& operator = (const Singleton& other) = delete; //assignment operator - assigns a to b //delete = no one can assign

        static T& Instance()
        {
            static T instance;

            return instance;
        }

    protected:
        Singleton() = default; //no one can create a new instance since we're private
    };
}