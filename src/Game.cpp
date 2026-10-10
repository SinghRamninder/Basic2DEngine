#include "Game.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool Game::Initialize() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "Failed to initialize SDL" << SDL_GetError() << endl;
		return false;
	}

	if (!SDL_CreateWindowAndRenderer("2D Game", screenWidth, screenHeight, 0, &window, &renderer)) {
		cerr << "Failed to create window" << SDL_GetError() << endl;

		return false;
	}

	enemies.emplace_back(400.0f, 300.0f);
	enemies.emplace_back(700.0f, 500.0f);
	enemies.emplace_back(900.0f, 200.0f);

	lastFrame = SDL_GetPerformanceCounter();
	running = true;

	return true;
}

void Game::Run() {
	while (running) {
		ProcessInput();
		if (!gameOver) {
			Update();
		}
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}

		if (!gameOver) {
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					Vector2 playerPosition = player.GetCenter();
					Vector2 direction = Vector2::Direction(playerPosition, Vector2(event.button.x, event.button.y));

					projectiles.emplace_back(playerPosition, direction);
				}
			}
		}
	}
}

void Game::Update() {
	Uint64 currentFrame = SDL_GetPerformanceCounter();
	deltaTime = static_cast<float>(currentFrame - lastFrame) / static_cast<float>(SDL_GetPerformanceFrequency());
	lastFrame = currentFrame;

	const bool* keyboardState = SDL_GetKeyboardState(nullptr);
	player.Update(keyboardState, deltaTime);

	for (auto& projectile : projectiles) {
		projectile.Update(deltaTime);
	}

	Vector2 playerPosition = player.GetCenter();

	for (auto& enemy : enemies) {
		enemy.Update(deltaTime, playerPosition);
	}

	for (auto it = projectiles.begin(); it != projectiles.end();) {

		bool projectileHit = false;

		for (auto ij = enemies.begin(); ij != enemies.end();) {

			if (checkCollision(ij->GetRect(), it->GetRect())) {
				ij->TakeDamage(20.0f);
				projectileHit = true;

				if (ij->isDead()) {
					ij = enemies.erase(ij);
				}

				break;

			} else {
				++ij;
			}
		}

		if (projectileHit) {
			it = projectiles.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto& enemy : enemies) {
		if (checkCollision(enemy.GetRect(), player.GetRect()) && enemy.CanAttack()) {
			player.TakeDamage(10.0f);
			enemy.ResetAttackCooldown();
		}
	}

	erase_if(projectiles, [this](const Projectile& projectile) {
		return projectile.isOffScreen(screenWidth, screenHeight);
		});

	if (player.isDead()) {
		gameOver = true;
		cout << "Game Over!" << endl;
	}
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (!player.isDead()) {
		player.Render(renderer);
	}

	for (auto& projectile : projectiles) {
		projectile.Render(renderer);
	}

	for (auto& enemy : enemies) {
		enemy.Render(renderer);
	}

	RenderUI();

	SDL_RenderPresent(renderer);
}

void Game::RenderUI() {
	float healthPercentage = player.GetHealth() / player.GetMaxHealth();
	healthBar.w = healthBarBackground.w * healthPercentage;

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &healthBarBackground);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &healthBar);
}

bool Game::checkCollision(const SDL_FRect& a, const SDL_FRect& b) const {
	return !((a.x + a.w) < b.x || a.x > (b.x + b.w) || (a.y + a.h) < b.y || a.y > (b.y + b.h));
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