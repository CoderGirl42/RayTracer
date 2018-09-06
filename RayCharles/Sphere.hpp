#pragma once


#include "Entity.hpp"

class _MMX_ALIGN_ Sphere : public Entity
{
public:
	Sphere() {}
	Sphere(const Vec3& c, real r) : Center(c), Radius(r) {};
	virtual bool Hit(const Ray& r, real t_min, real t_max, HitRecord& rec);
	Vec3 Center;
	real Radius;
	Entity *Entity;

};

bool Sphere::Hit(const Ray& r, real t_min, real t_max, HitRecord& rec)
{
	Vec3 oc = r.Origin() - Center;
	real a = r.Direction().Dot(r.Direction());
	real b = oc.Dot(r.Direction());
	real c = oc.Dot(oc) - Radius * Radius;

	real discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - SQRT(b * b - a * c)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - Center) / Radius;
			rec.e = this;
			return true;
		}

		temp = (-b + SQRT(b * b - a * c)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - Center) / Radius;
			rec.e = this;
			return true;
		}
	}

	return false;
}
