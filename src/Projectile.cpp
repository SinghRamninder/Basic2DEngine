#include "Projectile.h"

Projectile::Projectile(Vector2 spawnPos, Vector2 dir) {
	rect.x = spawnPos.x;
	rect.y = spawnPos.y;
	rect.w = 20.0f;
	rect.h = 20.0f;
	direction = dir;
}

void Projectile::Update(float deltaTime) {
	rect.x += direction.x * speed * deltaTime;
	rect.y += direction.y * speed * deltaTime;
}

void Projectile::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}