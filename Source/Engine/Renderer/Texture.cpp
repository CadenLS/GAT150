#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(std::string filename, ...)
	{
		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}

	bool Texture::Load(const std::string filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG("File not found" << filename);
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("Texture not found" << filename);
			return false;
		}
		return true;
	}
	// Get the size (width and height) of the texture
	vec2 Texture::GetSize() const
	{
		// ASSERT texture is not null (checks if the texture exists before proceeding)
		assert(m_texture != nullptr);

		// Get the width and height of the texture using SDL_QueryTexture
		SDL_Point point;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

		// Return the size as a vec2 (casting to float to avoid data loss)
		return vec2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
}