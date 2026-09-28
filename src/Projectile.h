#pragma once

#include <SDL3/SDL.h>
#include "Vector2.h"

class Projectile {
public:
	Projectile(Vector2 spawnPos, Vector2 dir);

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer) const;

private:
	SDL_FRect rect;
	float speed = 300.0f;
	Vector2 direction;
};