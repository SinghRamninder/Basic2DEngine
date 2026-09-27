#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Vector2.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "Failed to initialize SDL" << SDL_GetError() << endl;

        return 1;
    }

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("2D Game", 1920, 1080, 0, &window, &renderer)) {
		cerr << "Failed to create window" << SDL_GetError() << endl;

		SDL_Quit();
		return 1;
    }

	bool running = true;

	Uint64 lastFrame = SDL_GetPerformanceCounter();

	SDL_FRect playerRect{
			100.0f,
			100.0f,
			50.0f,
			50.0f
	};

	Vector2 direction;
	float playerSpeed = 100.0f;

	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		Uint64 currentFrame = SDL_GetPerformanceCounter();
		float deltaTime = static_cast<float>(currentFrame - lastFrame) / static_cast<float>(SDL_GetPerformanceFrequency());
		lastFrame = currentFrame;

		direction.x = 0.0f;
		direction.y = 0.0f;

		const bool* keyboardState = SDL_GetKeyboardState(nullptr);

		if (keyboardState[SDL_SCANCODE_W]) {
			direction.y -= 1.0f;
		}
		if (keyboardState[SDL_SCANCODE_S]) {
			direction.y += 1.0f;
		}
		if (keyboardState[SDL_SCANCODE_A]) {
			direction.x -= 1.0f;
		}
		if (keyboardState[SDL_SCANCODE_D]) {
			direction.x += 1.0f;
		}

		direction.Normalize();

		playerRect.x += direction.x * playerSpeed * deltaTime;
		playerRect.y += direction.y * playerSpeed * deltaTime;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &playerRect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}