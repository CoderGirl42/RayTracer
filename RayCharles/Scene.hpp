#pragma once

#include "Entity.hpp"

class Scene : public Entity
{
public:
	Scene() {}
	Scene(Entity **e, int n) { list = e; list_size = n; }
	virtual bool Hit(const Ray& r, real t_min, real t_max, HitRecord& rec);
	Entity **list;
	int list_size;
};

bool Scene::Hit(const Ray& r, real t_min, real t_max, HitRecord& rec)
{
	HitRecord temp_rec;
	bool hit = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->Hit(r, t_min, closest_so_far, temp_rec))
		{
			hit = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit;
}