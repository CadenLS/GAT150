#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"

#include "StarField.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

using vec2 = kiko::Vector2;

class Star
{
public:
	Star(kiko::Vector2& pos, kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}
	void Update()
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

int main(int argc, char* argv[])
{
	kiko::MemoryTracker::Initialize();

	bool quit = false;
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;



	kiko::Renderer renderer;
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_audioSystem.Initialize();
	kiko::g_inputSystem.Initialize();

	// Create Game
	unique_ptr<StarField> game = make_unique<StarField>();
	game->Initialize();

	kiko::vec2 v{ 5, 5 };
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kiko::Transform transform{ {400, 300}, 0, 3 };

	kiko::vec2 position{ 400, 300 };

	float speed = 200;
	constexpr float turnRate = kiko::DegreesToRadians(180);

	while (!quit)
	{
		// engine update
		kiko::g_time.Tick();
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// game update
		game->Update(kiko::g_time.GetDeltaTime());

		/*if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
		{
			cout << "Mouse Button Pressed" << endl;
			cout << kiko::g_inputSystem.GetMousePosition().x << endl;
			cout << kiko::g_inputSystem.GetMousePosition().y << endl;
		}*/

		//if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		//{
		//	kiko::g_audioSystem.PlayOneShot("Laser");
		//}
			kiko::g_audioSystem.PlayOneShot("Sound", true);


		// draw game
		for (auto& star : stars)
		{ 
			star.Update();

			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			kiko::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		game->Draw(kiko::g_renderer);

		//text->Draw(kiko::g_renderer, 400, 300);

		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;

}