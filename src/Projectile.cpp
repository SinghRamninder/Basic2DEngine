#include "Projectile.h"

Projectile::Projectile(Vector2 spawnPos, Vector2 dir) {
	rect.w = 20.0f;
	rect.h = 20.0f;
	rect.x = spawnPos.x - (rect.w/2.0f);
	rect.y = spawnPos.y - (rect.h/2.0f);
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

bool Projectile::isOffScreen(int screenWidth, int screenHeight) const {
	return rect.x + rect.w < 0 || rect.x > screenWidth || rect.y + rect.h < 0 || rect.y > screenHeight;
}