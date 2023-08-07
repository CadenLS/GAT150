#pragma once
#include "Core/Vector2.h"
#include "Framework/Resource/Resource.h"

struct SDL_Texture;

namespace kiko
{
	class Texture : Resource
	{
	public:
		Texture() = default;
		~Texture();

		virtual bool Create(std::string filename, ...) override;

		bool Load(const std::string filename, class Renderer& renderer);
		vec2 GetSize();

		SDL_Texture* GetTexture() const { return m_texture; }

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;

	};
}