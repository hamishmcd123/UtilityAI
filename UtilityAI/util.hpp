#pragma once

inline float clamp01(float x) {
	return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline float smoothStep01(float x) {
	x = clamp01(x);
	return x * x * (3 - 2 * x);
}