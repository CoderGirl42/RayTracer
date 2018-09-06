#pragma once

#include "Ray.hpp"

class Camera
{
public:
	Camera() {
		BottomLeftCorner = Vec3(-2.0, -1.0, -1.0);
		Horizontal = Vec3(4.0, 0.0, 0.0);
		Vertical = Vec3(0.0, 2.0, 0.0);
		Origin = Vec3(0.0, 0.0, 0.0);

	}

	inline Ray GetRay(const real u, const real v) const {
		return Ray(Origin, BottomLeftCorner + u * Horizontal + v * Vertical - Origin);
	}

	Vec3 Origin;
	Vec3 BottomLeftCorner;
	Vec3 Horizontal;
	Vec3 Vertical;
};