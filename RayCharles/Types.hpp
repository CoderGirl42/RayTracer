#pragma once

#ifndef _TYPES_H_
#define _TYPES_H_

#include <cmath>
#include <iostream>
#include "Math.hpp"

typedef int64_t		int64;
typedef int32_t		int32;
typedef int16_t		int16;
typedef int8_t		int08;

typedef uint64_t	uint64;
typedef uint32_t	uint32;
typedef uint16_t	uint16;
typedef uint8_t		uint08;

typedef float		real32;
typedef long double real64;

template <typename T, typename I> class _Vec2;
template <typename T, typename I> class _Vec3;
template <typename T, typename I> class _Vec4;

#if defined	__DOUBLE_PRECISION__

typedef long double _MMX_ALIGN_				   real;
typedef class _MMX_ALIGN_ _Vec2<real, __m256d> Vec2;
typedef class _MMX_ALIGN_ _Vec3<real, __m256d> Vec3;
typedef class _MMX_ALIGN_ _Vec4<real, __m256d> Vec4;

#elif defined __SINGLE_PRECISION__

typedef float _MMX_ALIGN_				      real;
typedef class _MMX_ALIGN_ _Vec2<real, __m128> Vec2;
typedef class _MMX_ALIGN_ _Vec3<real, __m128> Vec3;
typedef class _MMX_ALIGN_ _Vec4<real, __m128> Vec4;

#endif

real32 AsReal32(uint32 i);
real64 AsReal64(uint64 i);

//
//inline Vec2 UnitVector(const Vec2& v)								{ return v.UnitVector();																									}
//inline Vec3 UnitVector(const Vec3& v)								{ return v.UnitVector();																									}
//inline Vec4 UnitVector(const Vec4& v)								{ return v.UnitVector();																									}
//
//inline real Dot(const Vec3 &v0, const Vec3 &v1)						{ return MMX_GET_REAL(MMX_DOT_REAL(v0(), v1()), 0); }
//inline real Dot(const Vec4& v0, const Vec4& v1)						{ Vec4 c(MMX_MUL_REAL(v0(), v1())); return c.x() + c.y() + c.z() + c.w();													}
//
//inline Vec3 Cross(const Vec3 &v0, const Vec3 &v1)					{
//	//return Vec3(v1.y() * v2.z() - v1.z() * v2.y(), -(v1.x() * v2.z() - v1.x() * v2.z()), v1.x() * v2.y() - v1.y() * v2.x());	
//	return MMX_CROSS_REAL(v0(), v1());
//}


#endif
