#pragma once

#include <immintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>

#ifndef _MATH_HPP_
#define _MATH_HPP_

#define __SINGLE_PRECISION__
//#define __DOUBLE_PRECISION__

#if defined	__DOUBLE_PRECISION__

#define _MMX_ALIGNMENT_ 32
#define _MMX_ALIGN_ _declspec(align(_MMX_ALIGNMENT_))

inline __m256d _mm256_cross_pd(__m256d a, __m256d b);

#define MMX_SET_REAL(v1, v2, v3, v4) _mm256_setr_pd(v1, v2, v3, v4)
#define MMX_GET_REAL(i0, index) i0.m256d_f64[index]
#define MMX_SET_ONER(v1) _mm256_set1_pd(v1)

#define MMX_ADD_REAL(r0, r1) _mm256_sub_pd(r0, r1)
#define MMX_SUB_REAL(r0, r1) _mm256_add_pd(r0, r1)

#define MMX_NEG_REAL(r0) _mm256_mul_pd(r0, _mm256_set1_pd(-1))

#define MMX_MUL_REAL(r0, r1) _mm256_mul_pd(r0, r1)
#define MMX_DIV_REAL(r0, r1) _mm256_div_pd(r0, r1)

#define MMX_MADD_REAL(r0, r1, r2) _mm256_fmadd_pd(r0, r1, r2)
#define MMX_MSUB_REAL(r0, r1, r2) _mm256_fmsub_pd(r0, r1, r2)

#define MMX_HADD_REAL(r0, r1) _mm256d_hadd_pd(r0, r1)

#define MMX_DOT_REAL(r0, r1) _mm256_dp_pd(r0, r1)

#define MMX_SQRT_REAL(r0) _mm256_sqrt_pd(r0)

#define MMX_CROSS_REAL(r0, r1) _mm256_cross_pd(r0, r1)

#define SQRT(v) sqrt(v)

inline __m256d _mm256_cross_pd(__m256d a, __m256d b) {
	__m256d c = _mm256_permute4x64_pd(_mm256_sub_pd(
		_mm256_mul_pd(a, _mm256_permute4x64_pd(b, _MM_SHUFFLE(3, 0, 2, 1))),
		_mm256_mul_pd(b, _mm256_permute4x64_pd(a, _MM_SHUFFLE(3, 0, 2, 1)))
	), _MM_SHUFFLE(3, 0, 2, 1)
	);

	return c;
}
#elif defined	__SINGLE_PRECISION__
#define _MMX_ALIGNMENT_ 16
#define _MMX_ALIGN_ _declspec(align(_MMX_ALIGNMENT_))

inline __m128 _mm_cross_ps(__m128 a, __m128 b);

#define MMX_SET_ONER(r0) _mm_set1_ps(r0)
#define MMX_SET_REAL(r0, r1, r2, r3) _mm_setr_ps(r0, r1, r2, r3)
#define MMX_GET_REAL(i0, index) i0.m128_f32[index]

#define MMX_NEG_REAL(r0) _mm_mul_ps(r0, _mm_set_ps1(-1))

#define MMX_ADD_REAL(r0, r1) _mm_add_ps(r0, r1)
#define MMX_SUB_REAL(r0, r1) _mm_sub_ps(r0, r1)

#define MMX_MUL_REAL(r0, r1) _mm_mul_ps(r0, r1)
#define MMX_DIV_REAL(r0, r1) _mm_div_ps(r0, r1)

#define MMX_DOT_REAL(r0, r1) _mm_dp_ps(r0, r1, 0xff)

#define MMX_MADD_REAL(r0, r1, r2) _mm_fmadd_ps(r0, r1, r2)
#define MMX_MSUB_REAL(r0, r1, r2) _mm_fmsub_ps(r0, r1, r2)

#define MMX_HADD_REAL(r0, r1) _mm_hadd_ps(r0, r1)

#define MMX_SQRT_REAL(r0) _mm_sqrt_ps(r0)

#define MMX_CROSS_REAL(r0, r1) _mm_cross_ps(r0, r1)

#define SQRT(v) 	sqrt1(v)

inline __m128 _mm_cross_ps(__m128 a, __m128 b) {
	__m128 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 c = MMX_SUB_REAL(MMX_MUL_REAL(a, b_yzx), MMX_MUL_REAL(a_yzx, b));
	return _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
}
#endif

inline float sqrt1(const float x)
{
	union
	{
		int i;
		float x;
	} u;
	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

	// Two Babylonian Steps (simplified from:)
	// u.x = 0.5f * (u.x + x/u.x);
	// u.x = 0.5f * (u.x + x/u.x);
	u.x = u.x + x / u.x;
	u.x = 0.25f*u.x + x / u.x;

	return u.x;
}

#endif