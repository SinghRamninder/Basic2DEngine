#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"

class Enemy {
public:
	Enemy(float x, float y);

	void Update(float deltaTime, Vector2 playerPosition);
	void Render(SDL_Renderer* renderer) const;
	Vector2 GetCenter() const;

private:
	SDL_FRect rect;
	float speed = 100.0f;
	float health = 100.0f;
	Vector2 direction;
};