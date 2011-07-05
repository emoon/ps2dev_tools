/*
 * mmi-intrinsics.h - R5900 MMI compiler intrinsics.
 *
 * Copyright (c) 2003  M. R. Brown <mrbrown@0xd6.org>
 *
 * This file is licensed under the GNU GPL version 2.
 *
 * As a special exception, if you include this header file into source
 * files compiled by GCC, this header file does not by itself cause
 * the resulting executable to be covered by the GNU General Public
 * License.  This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU General
 * Public License.
 *
 */

/* Based off of the mmintrin.h file in GCC 3.2.1 */

#ifndef __mmi_intrinsics_h
#define __mmi_intrinsics_h

/* This for user programs. */
typedef int __m128 __attribute__ ((mode(TI)));

#define __vector __attribute__((vector_size(16)))

/* These are internal. */
typedef int __v16qi __attribute__ ((mode(V16QI)));
typedef int __v8hi __attribute__ ((mode(V8HI)));
typedef int __v4si __attribute__ ((mode(V4SI)));

#if !defined(__u128)
typedef unsigned int __u128 __attribute__((mode(TI)));
#endif
#if !defined(__s128)
typedef __signed__ int __s128 __attribute__((mode(TI)));
#endif

/* Convert i to a __m128 object.  The integer is zero-extended to 128-bits. */
/* XXX: No, not really.  Figure out why. */
static __inline __m128 _mmi_cvtsi32_si128(int i)
{
	__u128 tmp = (unsigned int)i;
	return (__m128)tmp;
}

/* Add the 8-bit values in m1 to the 8-bit values in m2. */

static inline __m128
_mmi_paddb(__m128 m1, __m128 m2)
{
	return (__m128) __builtin_mmi_paddb((__v16qi)m1, (__v16qi)m2);
}

/* Creates a vector of two 64-bit values; d0 is least significant. */
static inline __m128
_mmi_create_vec64(long d1, long d0)
{
	union {
		__m128 q;
		struct {
			unsigned long d0;
			unsigned long d1;
		} s;
	} u;

	u.s.d0 = d0;
	u.s.d1 = d1;
	return u.q;
}

/* Convienence routines for creating vectors. */

/* Creates a vector of 4 32-bit values; w0 is least significant. */
static inline __m128
_mmi_create_vec32(int w3, int w2, int w1, int w0)
{
	unsigned long d1 = (unsigned int)w3 << 32 | (unsigned int)w2;
	unsigned long d0 = (unsigned int)w1 << 32 | (unsigned int)w0;
	return _mmi_create_vec64(d1, d0);
}

/* Creates a vector of 8 16-bit values; h0 is least significant. */
static inline __m128
_mmi_create_vec16(short h7, short h6, short h5, short h4,
		  short h3, short h2, short h1, short h0)
{
	unsigned long d1, d0;

	d1 = (unsigned short)h7;
	d1 = d1 << 16 | (unsigned short)h6;
	d1 = d1 << 16 | (unsigned short)h5;
	d1 = d1 << 16 | (unsigned short)h4;

	d0 = (unsigned short)h3;
	d0 = d0 << 16 | (unsigned short)h2;
	d0 = d0 << 16 | (unsigned short)h1;
	d0 = d0 << 16 | (unsigned short)h0;

	return _mmi_create_vec64(d1, d0);
}

#endif /* __mmi_intrinsics_h */

