#pragma once

#include "Types.hpp"
#include "Vector.hpp"

class Ray
{
public:
	Ray() {}
	Ray(const Vec3& a, const Vec3& b/*, float ti = 0.0f*/) { A = a; B = b; /*_time = ti;*/ ray_count++; }
	inline Vec3 Origin() const { return A; }
	inline Vec3 Direction() const { return B; }
	inline Vec3 PointAtParameter(real t) const { return A + t * B; }

	//float time() const { return _time; }

	Vec3 A;
	Vec3 B;
	//float _time;

	static long ray_count;
};

long Ray::ray_count;