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
};