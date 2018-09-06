#pragma once

#include "Ray.hpp"


class Entity;
class Material;

struct HitRecord
{
	real t;
	Vec3 p;
	Vec3 normal;
	Material *m;
	Entity *e;

};

class Entity {
public:
	virtual bool Hit(const Ray& r, real t_min, real t_max, HitRecord& rec) = 0;
};