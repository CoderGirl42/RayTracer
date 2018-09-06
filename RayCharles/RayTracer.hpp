#pragma once

class Scene;
#include "Types.hpp"

enum SurfaceFormat
{
	COLOR_FORMAT_D32	= 1,
	COLOR_FORMAT_RGBA32 = 2,
	COLOR_FORMAT_ARGB32 = 3
};

class RayTracer
{
protected:
	virtual void LockSurface();
	virtual void UnlockSurface();

	virtual void FreeSurface();
	virtual void* AllocateSurface(const uint32 surfaceHeight, const uint32 surfaceWidth, const SurfaceFormat surfaceFormat);

public:
	RayTracer(Scene* scene, const uint32 surfaceHeight, const uint32 surfaceWidth, const SurfaceFormat surfaceFormat);
	
	virtual void Start();
	virtual void Stop();
	virtual void Clear();
	virtual void Fill(const uint08& r, const uint08& g, const uint08& b, const uint08& a);
	virtual void ResetCounters();

	virtual void SetScene(Scene* scene);

	virtual bool ResizeSurface(const uint32 surfaceHeight, const uint32 surfaceWidth);	
	
	virtual uint32			Width()				const;
	virtual uint32			Height()			const;
	virtual SurfaceFormat	Format()			const;
	virtual uint08			SurfaceComponents() const;
	virtual void*			GetSurface()		const;
	virtual Scene*			GetScene()			const;
	virtual bool			IsTracing()			const;
	virtual bool			IsAllocated()		const;
	virtual bool			IsLocked()			const;
	virtual uint64			NumRays()			const;
	virtual uint64			NumPixels()			const;
	virtual uint64			TraceTime()			const;

private:
	uint64 m_numRays = 0;
	uint64 m_numPixels = 0;
	uint64 m_traceTime = 0;

	uint32 m_surfaceHeight = 0;
	uint32 m_surfaceWidth = 0;
	uint08 m_surfaceComps = 0;

	Scene* m_scene = nullptr;
	SurfaceFormat m_surfaceFormat;

	bool m_isTracing = false;
	bool m_isLocked = false;
	bool m_isAllocated = false;

protected:
	void* m_surface = 0;

};