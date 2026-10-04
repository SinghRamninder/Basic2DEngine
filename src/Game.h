#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

class Game
{
public:

    ~Game();

    bool Initialize();

    void Run();

private:
    void ProcessInput();

    void Update();

    void Render();

	bool checkCollision(const SDL_FRect& a, const SDL_FRect& b) const;

private:
	int screenWidth = 1920;
	int screenHeight = 1080;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool running = false;

    Uint64 lastFrame = 0;

    float deltaTime = 0.0f;

    Player player{100.0f, 100.0f};

	std::vector<Projectile> projectiles;
    std::vector<Enemy> enemies;
};