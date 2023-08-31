#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"

#include <map>
#include <string>
#include <memory>

//macro // type = resource type we're getting // filename = name of file // ... = any other thing we need
#define GET_RESOURCE(type, filename, ...) kiko::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace kiko
{
    class ResourceManager : public Singleton<ResourceManager>
    {
    public:
        template<typename T, typename ... TArgs>
        res_t<T> Get(const std::string& filename, TArgs ... args);

    private:
        std::map<std::string, res_t<Resource>> m_resources;
    };

    template<typename T, typename ... TArgs>
    std::shared_ptr<T> ResourceManager::Get(const std::string& filename, TArgs ... args)
    {
        // Check if the resource with the given filename already exists in the resource map.
        if (m_resources.find(filename) != m_resources.end())
        {
            // If it exists, return the existing resource after casting it to type T.
            // std::dynamic_pointer_cast is used to safely downcast the base Resource pointer to a derived T pointer.
            return std::dynamic_pointer_cast<T>(m_resources[filename]);
        }

        res_t<T> resource = std::make_shared<T>();
        if (!resource->Create(filename, args...))
        {
            WARNING_LOG("Could not create resource: " << filename);
            return res_t<T>();
        }

        m_resources[filename] = resource;
        return resource;
    }
};