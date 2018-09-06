#pragma once

#include "Ray.hpp"
#include "Rand.hpp"
#include "Types.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "RayTracer.hpp"
#include "Stopwatch.hpp"
#include <iostream>

//inline Vec3 hit_sphere(const Vec3& center, const Vec3& radius, const Ray& r)
//{
//	Vec3 rs(radius * radius);
//	Vec3 oc(r.Origin() - center);
//	Vec3 a(MMX_SET_ONER(r.Direction().Dot(r.Direction())));
//	Vec3 b(MMX_MUL_REAL(MMX_SET_ONER(2.0), MMX_SET_ONER(oc.Dot(r.Direction()))));
//	Vec3 c(MMX_SUB_REAL(MMX_SET_ONER(oc.Dot(oc)), rs()));
//	Vec3 d(MMX_SUB_REAL(MMX_MUL_REAL(b(), b()), (MMX_MUL_REAL(MMX_SET_ONER(4.0), MMX_MUL_REAL(a(), c())))));
//
//	if (MMX_GET_REAL(_mm_cmplt_ps(d(), MMX_SET_ONER(0)), 0)) {
//		return { -1.0, -1.0, -1.0 };
//	} else {
//		return Vec3(MMX_DIV_REAL(MMX_SUB_REAL(MMX_NEG_REAL(b()), MMX_SQRT_REAL(d())), (MMX_MUL_REAL(MMX_SET_ONER(2.0), a()))));
//	}
//}
//
//Vec4 color(const Ray& r)
//{
//	Vec3 t = hit_sphere({ 0.0, 0.0, -1.0 }, { 0.5, 0.5, 0.5 }, r);
//
//	if (MMX_GET_REAL(_mm_cmpgt_ps(t(), Vec2()()), 0))
//	{
//		Vec3 N = r.PointAtParameter(MMX_GET_REAL(t(), 0)) - Vec3(0.0, 0.0, -1.0).UnitVector();
//
//		return 0.5 * Vec4(N + 1.0, 1.0);
//	}
//
//	Vec3 unit_direction = r.Direction().UnitVector();
//
//	t = Vec3(0.5, 0.5, 0.5) * MMX_SET_ONER(unit_direction.y()) + Vec3(1.0, 1.0, 1.0);
//
//	return Vec4((Vec3(1.0, 1.0, 1.0) - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
//}

Vec3 RandomInUnitSphere() {
	Vec3 p;
	do
	{
		p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
	} while (p.SquaredLength() >= 1.0);

	return p;
}

Vec3 Color(const Ray& r, Entity* world)
{
	HitRecord rec;

	if (world->Hit(r, 0.0001, FLT_MAX, rec))
	{
		Vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		return 0.5 * Color(Ray(rec.p, target - rec.p), world);
	}
	else
	{
		Vec3 unit_direction = r.Direction().UnitVector();
		real t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

RayTracer::RayTracer(Scene* scene, const uint32 surfaceHeight, const uint32 surfaceWidth, const SurfaceFormat surfaceFormat)
{
	m_scene = scene;
	m_surfaceHeight = surfaceHeight;
	m_surfaceWidth = surfaceWidth;
	m_surfaceFormat = surfaceFormat;

	m_surfaceComps = SurfaceComponents();

	AllocateSurface(m_surfaceHeight, m_surfaceWidth, surfaceFormat);
}

void RayTracer::Clear()
{
	if (m_isAllocated && !m_isLocked) 
	{
		Stopwatch* timer = new Stopwatch();
		
		LockSurface();
		memset(m_surface, 0, sizeof(uint32) * m_surfaceHeight * m_surfaceWidth);
		UnlockSurface();

		m_traceTime = timer->elapsed().count();
	}
}

#define __TRACE_UNROLLED__
void RayTracer::Start()
{
	if (m_isAllocated && !m_isLocked && !m_isTracing)
	{
		Camera cam;
		int ns = 100;
		Stopwatch* timer = new Stopwatch();

		Entity *list[2];
		list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
		list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
		Entity *world = new Scene(list, 2);

		m_isTracing = true;
		LockSurface();

		int08 components = SurfaceComponents();

#ifdef __TRACE_UNROLLED__
		int64 totalComponents = (m_surfaceHeight * m_surfaceWidth) * components;

	//	#pragma omp parallel for schedule(guided)
		for (int32 index = 0; index < totalComponents; index += components)
		{
			uint32 i = index / components;
			uint32 x = static_cast<int>(i % m_surfaceWidth);
			uint32 y = static_cast<int>(i / m_surfaceWidth);
#else
		#pragma omp parallel for schedule(static)
		for (int32 x = 0; x < m_surfaceWidth; x++)
		#pragma omp parallel for schedule(static)
		for (int32 y = 0; y < m_surfaceHeight; y++) 
		{
			uint64 index = (components * x) + m_surfaceWidth * (components * y);
#endif
			Vec3 col(0.0, 0.0, 0.0);

			for (int s = 0; s < ns; s++)
			{
				real u = real(x + drand48()) / real(m_surfaceWidth);
				real v = real(y + drand48()) / real(m_surfaceHeight);

				Ray r = cam.GetRay(u, v);

				col += Color(r, world);
			}

			col /= real(ns);
			col = MMX_SQRT_REAL(col());
			col *= real(255.99);

			((uint08*)m_surface)[index + 0] = (uint08)(col.r());
			((uint08*)m_surface)[index + 1] = (uint08)(col.g());
			((uint08*)m_surface)[index + 2] = (uint08)(col.b());
			((uint08*)m_surface)[index + 3] = (uint08)(255.99f);

			m_numRays++;
			m_numPixels++;

			if (!m_isTracing)
				break;
		}

		UnlockSurface();
		m_isTracing = false;
		m_traceTime = timer->elapsed().count();
	}
}

void RayTracer::Stop()
{
	m_isTracing = false;
}

void RayTracer::ResetCounters()
{
	m_numRays = 0;
	m_numPixels = 0;
	m_traceTime = 0;
}

void RayTracer::Fill(const uint08& r, const uint08& g, const uint08& b, const uint08& a)
{
	if (m_isAllocated && !m_isLocked)
	{
		Stopwatch* timer = new Stopwatch();
		m_isTracing = true;
		LockSurface();
		uint32 col;

		switch (m_surfaceFormat)
		{
			case SurfaceFormat::COLOR_FORMAT_RGBA32:
				col = a << 24 | b << 16 | g << 8 | r;
				break;
			case SurfaceFormat::COLOR_FORMAT_ARGB32:
				col = b << 24 | g << 16 | r << 8 | a;
				break;
		}

		std::fill(&reinterpret_cast<uint32*>(m_surface)[0], &reinterpret_cast<uint32*>(m_surface)[(m_surfaceWidth * m_surfaceHeight) - 1], col);

		UnlockSurface();
		m_isTracing = false;
		m_traceTime = timer->elapsed().count();
	}
}

void RayTracer::SetScene(Scene* scene)
{

}

void RayTracer::LockSurface()
{
	m_isLocked = true;
}

void RayTracer::UnlockSurface()
{
	m_isLocked = false;
}

void RayTracer::FreeSurface()
{
	if (m_isAllocated && !m_isLocked)
	{
		LockSurface();
		free(m_surface);
		UnlockSurface();
		m_isAllocated = false;
	}
}

bool RayTracer::ResizeSurface(const uint32 surfaceHeight, const uint32 surfaceWidth)
{
	if (m_isAllocated && !m_isLocked)
	{

		FreeSurface();

		LockSurface();
		m_surface = new uint08[sizeof(uint32) * surfaceHeight * surfaceWidth];
		UnlockSurface();

		m_isAllocated = true;
		return true;
	}

	return false;
}

void* RayTracer::AllocateSurface(const uint32 surfaceHeight, const uint32 surfaceWidth, const SurfaceFormat surfaceFormat)
{
	if(!m_isAllocated && !m_isLocked )
	{
		m_surfaceFormat = surfaceFormat;
		m_surfaceComps = SurfaceComponents();

		m_surfaceHeight = surfaceHeight;
		m_surfaceWidth = surfaceWidth;

		LockSurface();
		m_surface = new uint08[sizeof(uint32) * m_surfaceHeight * m_surfaceWidth];
		UnlockSurface();

		m_isAllocated = true;
		return m_surface;
	}

	return nullptr;
}
	

uint32 RayTracer::Width() const
{
	return m_surfaceWidth;
}

uint32 RayTracer::Height() const
{
	return m_surfaceHeight;
}

SurfaceFormat RayTracer::Format() const
{
	return m_surfaceFormat;
}

uint08 RayTracer::SurfaceComponents() const
{
	switch (m_surfaceFormat)
	{
	case SurfaceFormat::COLOR_FORMAT_D32:
		return 1;
	case SurfaceFormat::COLOR_FORMAT_ARGB32:
		return 4;
	case SurfaceFormat::COLOR_FORMAT_RGBA32:
		return 4;
	default: 
		return 0;
	}
}

void* RayTracer::GetSurface() const
{
	return m_surface;
}

Scene* RayTracer::GetScene() const
{
	return m_scene;
}

bool RayTracer::IsTracing()	const
{
	return m_isTracing;
}

bool RayTracer::IsAllocated() const
{
	return m_isAllocated;
}

bool RayTracer::IsLocked() const
{
	return m_isLocked;
}

uint64 RayTracer::NumRays() const
{
	return m_numRays;
}

uint64 RayTracer::NumPixels() const
{
	return m_numPixels;
}

uint64 RayTracer::TraceTime() const
{
	return m_traceTime;
}

