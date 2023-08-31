#include "PlatformGame.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Logger.h"
#include "Renderer/Texture.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>
#include <cassert>
#include <array>
#include <map>
#include <functional>

using namespace std;

using vec2 = kiko::Vector2;


int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("Assets/Platformer");

	// Initialize Engine
	//kiko::Renderer renderer;
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("GAT150", 1085, 600);

	kiko::g_audioSystem.Initialize();
	kiko::g_inputSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();

	// Create Game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	bool quit = false;
	while (!quit)
	{
		// engine update
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// update game
		kiko::g_audioSystem.PlayOneShot("Soundss", true);
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);
		kiko::g_renderer.EndFrame();
	}

	return 0;

}


//{
//	"type": "Actor",
//		"tag" : "Ground",
//		"transform" : {
//		"position": [
//			400,
//				520
//		]
//	},
//		"components": [
//	{
//		"type": "Box2DPhysicsComponent",
//			"isDynamic" : false
//	},
//				{
//					"type": "Box2DCollisionComponent",
//					"size" : [600, 20]
//				}
//		]
//},