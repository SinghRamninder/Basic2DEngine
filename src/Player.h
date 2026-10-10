#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"

class Player
{
public:
    Player(float x, float y);

    void Update(const bool* keyboardState, float deltaTime);
    void Render(SDL_Renderer* renderer) const;
    void TakeDamage(float damage);
    bool isDead() const;
    Vector2 GetCenter() const;
    const SDL_FRect& GetRect() const;

private:
    SDL_FRect rect;
    float speed = 200.0f;
	float health = 100.0f;
};