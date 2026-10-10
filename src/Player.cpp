#include "Player.h"

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

void Player::TakeDamage(float damage) {
	health -= damage;
}

bool Player::isDead() const {
	return health <= 0.0f;
}

float Player::GetHealth() const {
	return health;
}

float Player::GetMaxHealth() const {
	return maxHealth;
}

Vector2 Player::GetCenter() const {
	float centerX = rect.x + (rect.w / 2.0f);
	float centerY = rect.y + (rect.h / 2.0f);
	return Vector2(centerX, centerY);
}

const SDL_FRect& Player::GetRect() const {
	return rect;
}