#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Player.h"
#include "Projectile.h"

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

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool running = false;

    Uint64 lastFrame = 0;

    float deltaTime = 0.0f;

    Player player{100.0f, 100.0f};

	std::vector<Projectile> projectiles;
};