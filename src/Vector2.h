#pragma once

#include <cmath>

struct Vector2 {
	float x, y;

	float Length() const {
		return std::sqrt(x * x + y * y);
	}

	void Normalize() {
		float length = Length();

		if (length > 0.0f) {
			x /= length;
			y /= length;
		}
	}

	static Vector2 Direction(const Vector2& from, const Vector2& to) {
		Vector2 dir{ to.x - from.x, to.y - from.y };
		dir.Normalize();
		return dir;
	}
};