#pragma once

#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "Types.hpp"

template<typename T, typename I> class _MMX_ALIGN_ _Vec2
{
public:
	_Vec2() { e = MMX_SET_REAL(0.0, 0.0, 0.0, 0.0); }
	_Vec2(const I& val) { e = val; }
	_Vec2(const T& val) { e = MMX_SET_ONER(va); }
	_Vec2(const T& e0, const T& e1) { e = MMX_SET_REAL(e0, e1, 0.0, 0.0); }

	inline T x() const { return MMX_GET_REAL(e, 0); }
	inline T y() const { return MMX_GET_REAL(e, 1); }
	inline T r() const { return MMX_GET_REAL(e, 0); }
	inline T g() const { return MMX_GET_REAL(e, 1); }
	inline I operator()() const { return e; }

	inline _Vec2<T, I> operator-(void) const { return MMX_NEG_REAL(e); }
	inline _Vec2<T, I> operator-(const _Vec2<T, I> &v) const { return MMX_SUB_REAL(e, v.e); }
	inline _Vec2<T, I> operator-(const T t) const { return MMX_SUB_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec2<T, I> operator+(const _Vec2<T, I> &v) const { return MMX_ADD_REAL(e, v.e); }
	inline _Vec2<T, I> operator+(const T t) const { return MMX_ADD_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec2<T, I> operator*(const _Vec2<T, I> &v) const { return MMX_MUL_REAL(e, v.e); }
	inline _Vec2<T, I> operator*(const T t) const { return MMX_MUL_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec2<T, I> operator/(const _Vec2<T, I> &v) const { return MMX_DIV_REAL(e, v.e); }
	inline _Vec2<T, I> operator/(const T t) const { return MMX_DIV_REAL(e, MMX_SET_ONER(t)); }

	inline _Vec2<T, I>& operator+=(const _Vec2<T, I> &v) { e = MMX_ADD_REAL(e, v.e); return *this; }
	inline _Vec2<T, I>& operator+=(const T t) { e = MMX_ADD_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec2<T, I>& operator-=(const _Vec2<T, I> &v) { e = MMX_SUB_REAL(e, v.e); return *this; }
	inline _Vec2<T, I>& operator-=(const T t) { e = MMX_SUB_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec2<T, I>& operator*=(const _Vec2<T, I> &v) { e = MMX_MUL_REAL(e, v.e); return *this; }
	inline _Vec2<T, I>& operator*=(const T t) { e = MMX_MUL_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec2<T, I>& operator/=(const _Vec2<T, I> &v) { e = MMX_DIV_REAL(e, v.e); return *this; }
	inline _Vec2<T, I>& operator/=(const T t) { e = MMX_DIV_REAL(e, MMX_SET_ONER(t)); return *this; }

	inline T Length() const { _Vec2<T, I> c(MMX_MUL_REAL(e, e)); return SQRT(c.x() + c.y()); }
	inline T SquaredLength() const { _Vec2<T, I> c(MMX_MUL_REAL(e, e)); return c.x() + c.y(); }

	inline _Vec2<T, I> UnitVector()	const { return MMX_DIV_REAL(e, MMX_SET_ONER(Length())); }
	inline void MakeUnitVector() { e = MMX_MUL_REAL(e, MMX_DIV_REAL(MMX_SET_ONER(1.0), MMX_SET_ONER(Length()))); }

	inline T Dot(const _Vec2<T, I> &v) const {
		I r0 = MMX_MUL_REAL(e, v.e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		T r3 = MMX_GET_REAL(r2, 0);

		return r3;
	}

	inline void* operator new[](size_t size) { return _aligned_malloc(size, _MMX_ALIGNMENT_); }

	inline void operator delete[](void *v) { if (v) { _aligned_free(v); } }

protected:
	I e;
};


template<typename T, typename I> class _MMX_ALIGN_ _Vec3
{
public:
	_Vec3() { e = MMX_SET_REAL(0.0, 0.0, 0.0, 0.0); }
	_Vec3(const I& val) { e = val; }
	_Vec3(const T& val) { e = MMX_SET_ONER(val); }
	_Vec3(const _Vec2<T, I>& v) { e = MMX_SET_REAL(v.x, v.y, 0.0, 0.0); }
	_Vec3(const _Vec2<T, I>& v, const T& r0) { e = MMX_SET_REAL(v.x, v.y, r0, 0.0); }
	_Vec3(const T& r0, const T& r1, const T& r2) { e = MMX_SET_REAL(r0, r1, r2, 0.0); }

	inline T x() const { return MMX_GET_REAL(e, 0); }
	inline T y() const { return MMX_GET_REAL(e, 1); }
	inline T z() const { return MMX_GET_REAL(e, 2); }
	inline T r() const { return MMX_GET_REAL(e, 0); }
	inline T g() const { return MMX_GET_REAL(e, 1); }
	inline T b() const { return MMX_GET_REAL(e, 2); }
	inline I operator()() const { return e; }

	inline _Vec3<T, I> operator-(void) const { return MMX_NEG_REAL(e); }
	inline _Vec3<T, I> operator-(const _Vec3<T, I> &v) const { return MMX_SUB_REAL(e, v.e); }
	inline _Vec3<T, I> operator-(const T t) const { return MMX_SUB_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec3<T, I> operator+(const _Vec3<T, I> &v) const { return MMX_ADD_REAL(e, v.e); }
	inline _Vec3<T, I> operator+(const T t) const { return MMX_ADD_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec3<T, I> operator*(const _Vec3<T, I> &v) const { return MMX_MUL_REAL(e, v.e); }
	inline _Vec3<T, I> operator*(const T t) const { return MMX_MUL_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec3<T, I> operator/(const _Vec3<T, I> &v) const { return MMX_DIV_REAL(e, v.e); }
	inline _Vec3<T, I> operator/(const T t) const { return MMX_DIV_REAL(e, MMX_SET_ONER(t)); }

	inline _Vec3<T, I>& operator+=(const _Vec3<T, I> &v) { e = MMX_ADD_REAL(e, v.e); return *this; }
	inline _Vec3<T, I>& operator+=(const T t) { e = MMX_ADD_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec3<T, I>& operator-=(const _Vec3<T, I> &v) { e = MMX_SUB_REAL(e, v.e); return *this; }
	inline _Vec3<T, I>& operator-=(const T t) { e = MMX_SUB_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec3<T, I>& operator*=(const _Vec3<T, I> &v) { e = MMX_MUL_REAL(e, v.e); return *this; }
	inline _Vec3<T, I>& operator*=(const T t) { e = MMX_MUL_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec3<T, I>& operator/=(const _Vec3<T, I> &v) { e = MMX_DIV_REAL(e, v.e); return *this; }
	inline _Vec3<T, I>& operator/=(const float t) { e = MMX_DIV_REAL(e, MMX_SET_ONER(t)); return *this; }

	inline _Vec3<T, I> UnitVector() const { return MMX_DIV_REAL(e, MMX_SET_ONER(Length())); }
	inline void MakeUnitVector() { e = MMX_MUL_REAL(e, MMX_DIV_REAL(MMX_SET_ONER(1.0), MMX_SET_ONER(Length()))); }

	inline T Length() const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		I r3 = MMX_SQRT_REAL(r2);
		T r4 = MMX_GET_REAL(r3, 0);
		return r4;
	}

	inline T SquaredLength() const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		T r3 = MMX_GET_REAL(r2, 0);

		return r3;
	}


	inline T Dot(const _Vec3<T, I> &v) const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, v.e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		T r3 = MMX_GET_REAL(r2, 0);

		return r3;
	}

	inline _Vec3<T, I> Cross(const _Vec3<T, I> &v) const {
		//need to learn shuffles for this 
		//return _Vec3<T, I>(y() * v.z() - z() * v.y(), -(x() * v.z() - x() * v.z()), x() * v.y() - y() * v.x());	
		return MMX_CROSS_REAL(e, v.e);
	}

	inline void* operator new[](size_t size) { return _aligned_malloc(size, _MMX_ALIGNMENT_); }

	inline void operator delete[](void *v) { if (v) { _aligned_free(v); } }

protected:
	I e;
};

template<typename T, typename I> class _MMX_ALIGN_ _Vec4
{
public:
	_Vec4() { e = MMX_SET_REAL(0.0, 0.0, 0.0, 0.0); }
	_Vec4(const I& val) { e = val; }
	_Vec4(const T& val) { e = MMX_SET_ONER(val); }
	_Vec4(const _Vec2<T, I>& v0) { e = v0(); }
	_Vec4(const _Vec2<T, I>& v0, T z, T w) { e = MMX_SET_REAL(v0.x(), v0.y(), z, w); }
	_Vec4(const _Vec3<T, I>& v0) { e = v0(); }
	_Vec4(const _Vec3<T, I>&	v0, T w) { e = MMX_SET_REAL(v0.x(), v0.y(), v0.z(), w); }
	_Vec4(const T& r0, const T& r1, const T& r2, const T& r3) { e = MMX_SET_REAL(r0, r1, r2, r3); }

	inline T x() const { return MMX_GET_REAL(e, 0); }
	inline T y() const { return MMX_GET_REAL(e, 1); }
	inline T z() const { return MMX_GET_REAL(e, 2); }
	inline T w() const { return MMX_GET_REAL(e, 3); }
	inline T r() const { return MMX_GET_REAL(e, 0); }
	inline T g() const { return MMX_GET_REAL(e, 1); }
	inline T b() const { return MMX_GET_REAL(e, 2); }
	inline T a() const { return MMX_GET_REAL(e, 3); }
	inline I operator()() const { return e; }

	inline _Vec4<T, I> operator-(void) const { return MMX_NEG_REAL(e); }
	inline _Vec4<T, I> operator-(const _Vec4<T, I> &v) const { return MMX_SUB_REAL(e, v.e); }
	inline _Vec4<T, I> operator-(const T t) const { return MMX_SUB_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec4<T, I> operator+(const _Vec4<T, I> &v) const { return MMX_ADD_REAL(e, v.e); }
	inline _Vec4<T, I> operator+(const T t) const { return MMX_ADD_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec4<T, I> operator*(const _Vec4<T, I> &v) const { return MMX_MUL_REAL(e, v.e); }
	inline _Vec4<T, I> operator*(const T t) const { return MMX_MUL_REAL(e, MMX_SET_ONER(t)); }
	inline _Vec4<T, I> operator/(const _Vec4<T, I> &v) const { return MMX_DIV_REAL(e, v.e); }
	inline _Vec4<T, I> operator/(const T t) const { return MMX_DIV_REAL(e, MMX_SET_ONER(t)); }

	inline _Vec4<T, I>& operator+=(const _Vec4<T, I> &v) { e = MMX_ADD_REAL(e, v.e); return *this; }
	inline _Vec4<T, I>& operator+=(const T t) { e = MMX_ADD_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec4<T, I>& operator-=(const _Vec4<T, I> &v) { e = MMX_SUB_REAL(e, v.e); return *this; }
	inline _Vec4<T, I>& operator-=(const T t) { e = MMX_SUB_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec4<T, I>& operator*=(const _Vec4<T, I> &v) { e = MMX_MUL_REAL(e, v.e); return *this; }
	inline _Vec4<T, I>& operator*=(const T t) { e = MMX_MUL_REAL(e, MMX_SET_ONER(t)); return *this; }
	inline _Vec4<T, I>& operator/=(const _Vec4<T, I> &v) { e = MMX_DIV_REAL(e, v.e); return *this; }
	inline _Vec4<T, I>& operator/=(const T t) { e = MMX_DIV_REAL(e, MMX_SET_ONER(t)); return *this; }

	inline _Vec4<T, I> UnitVector() const { return MMX_DIV_REAL(e, MMX_SET_ONER(Length())); }
	inline void MakeUnitVector() { e = MMX_MUL_REAL(e, MMX_DIV_REAL(MMX_SET_ONER(1.0), MMX_SET_ONER(Length()))); }

	inline T Length() const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		I r3 = MMX_SQRT_REAL(r2);
		T r4 = MMX_GET_REAL(r3, 0);
		return r4;
	}

	inline T SquaredLength() const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		T r3 = MMX_GET_REAL(r2, 0);

		return r3;
	}

	inline real Dot(const _Vec4<T, I> &v) const {
		// OPTIMIZED?
		I r0 = MMX_MUL_REAL(e, v.e);
		I r1 = MMX_HADD_REAL(r0, r0);
		I r2 = MMX_HADD_REAL(r1, r1);
		T r3 = MMX_GET_REAL(r2, 0);

		return r3;
	}

	inline void* operator new[](size_t size) { return _aligned_malloc(size, _MMX_ALIGNMENT_); }

	inline void operator delete[](void *v) { if (v) { _aligned_free(v); } }
protected:
	I e;
};

inline Vec2 operator*(const real t, const Vec2& v) { return MMX_MUL_REAL(v(), MMX_SET_ONER(t)); }
inline Vec3 operator*(const real t, const Vec3& v) { return MMX_MUL_REAL(v(), MMX_SET_ONER(t)); }
inline Vec4 operator*(const real t, const Vec4& v) { return MMX_MUL_REAL(v(), MMX_SET_ONER(t)); }

#endif