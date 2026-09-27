#include "Player.h"
#include "Vector2.h"

Player::Player(float x, float y) {
	rect.x = x;
	rect.y = y;
	rect.w = 50.0f;
	rect.h = 50.0f;
}

void Player::Update(const bool* keyboardState, float deltaTime) {
	Vector2 direction{0.0f, 0.0f};

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

	rect.x += direction.x * speed * deltaTime;
	rect.y += direction.y * speed * deltaTime;
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}