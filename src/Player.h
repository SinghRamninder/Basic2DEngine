#pragma once

#include <SDL3/SDL.h>

class Player
{
public:
    Player(float x, float y);

    void Update(const bool* keyboardState, float deltaTime);
    void Render(SDL_Renderer* renderer) const;

private:
    SDL_FRect rect;
    float speed = 100.0f;
};