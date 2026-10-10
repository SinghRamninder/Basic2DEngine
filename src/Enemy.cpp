#include "Enemy.h"

Enemy::Enemy(float x, float y) {
	rect.x = x;
	rect.y = y;
	rect.w = 50.0f;
	rect.h = 50.0f;
}

void Enemy::Update(float deltaTime, Vector2 playerPosition) {
	Vector2 direction = Vector2::Direction(GetCenter(), playerPosition);

	rect.x += direction.x * speed * deltaTime;
	rect.y += direction.y * speed * deltaTime;

	if (attackCooldown > 0.0f) {
		attackCooldown -= deltaTime;
	}
}

void Enemy::TakeDamage(float damage) {
	health -= damage;
}

bool Enemy::isDead() const {
	return health <= 0.0f;
}

bool Enemy::CanAttack() const {
	return attackCooldown <= 0.0f;
}

void Enemy::ResetAttackCooldown() {
	attackCooldown = attackCooldownDuration;
}

void Enemy::Render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

Vector2 Enemy::GetCenter() const {
	float centerX = rect.x + (rect.w / 2.0f);
	float centerY = rect.y + (rect.h / 2.0f);
	return Vector2(centerX, centerY);
}

const SDL_FRect& Enemy::GetRect() const {
	return rect;
}