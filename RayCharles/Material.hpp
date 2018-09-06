#pragma once

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "Entity.hpp"

Vec3 RandomInUnitSphere() {
	Vec3 p;
	do
	{
		p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
	} while (p.SquaredLength() >= 1.0);

	return p;
}

class Material
{
public:
	virtual bool Scatter(const Ray& r, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Vec3& a) : albedo(0) {}
	virtual bool Scatter(const Ray& r, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = Albedo;
		return true;
	}
	Vec3 Albedo;
};

#endif
