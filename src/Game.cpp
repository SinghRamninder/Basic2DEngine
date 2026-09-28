#include "Game.h"
#include <iostream>
using namespace std;

bool Game::Initialize() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "Failed to initialize SDL" << SDL_GetError() << endl;
		return false;
	}

	if (!SDL_CreateWindowAndRenderer("2D Game", 1920, 1080, 0, &window, &renderer)) {
		cerr << "Failed to create window" << SDL_GetError() << endl;

		return false;
	}

	lastFrame = SDL_GetPerformanceCounter();
	running = true;

	return true;
}

void Game::Run() {
	while (running) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}

		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				Vector2 playerPos = player.GetCenter();
				Vector2 direction{
					event.button.x - playerPos.x,
					event.button.y - playerPos.y
				};
				direction.Normalize();
				projectiles.emplace_back(playerPos, direction);
			}
		}
	}
}

void Game::Update() {
	Uint64 currentFrame = SDL_GetPerformanceCounter();
	deltaTime = static_cast<float>(currentFrame - lastFrame) / static_cast<float>(SDL_GetPerformanceFrequency());
	lastFrame = currentFrame;

	for (auto& projectile : projectiles) {
		projectile.Update(deltaTime);
	}

	const bool* keyboardState = SDL_GetKeyboardState(nullptr);
	player.Update(keyboardState, deltaTime);
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player.Render(renderer);

	for (auto& projectile : projectiles) {
		projectile.Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

Game::~Game() {
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (window)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}