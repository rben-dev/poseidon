#ifndef __F251_H__
#define __F251_H__

#include <stdint.h>

// In case of non x86_64 platforms, undefine ASSEMBLY
#if defined(ASSEMBLY) && !defined(__x86_64__)
#undef ASSEMBLY
#endif

// Adapt the ABI to sysv one if we are dealing with a GNUC compiler for a Windows target
#if defined(ASSEMBLY) && defined(__GNUC__) && defined(__WIN32__)
#define SYSV_ABI __attribute__((sysv_abi))
#else
#define SYSV_ABI
#endif

typedef uint64_t felt_t[4];

////////////////////////////////////////////////////////////////////////////////
///  F251 basic operations
////////////////////////////////////////////////////////////////////////////////

void f251_copy(felt_t z, const felt_t x);
SYSV_ABI void f251_add(felt_t z, const felt_t x, const felt_t y);
SYSV_ABI void f251_sub(felt_t z, const felt_t x, const felt_t y);

////////////////////////////////////////////////////////////////////////////////
///  F251 "x +/- c*y" functions
////////////////////////////////////////////////////////////////////////////////

#ifdef ASSEMBLY

SYSV_ABI void f251_x_plus_c_times_y(felt_t z, const felt_t x, const uint32_t c, const felt_t y);
SYSV_ABI void f251_x_minus_c_times_y(felt_t z, const felt_t x, const uint32_t c, const felt_t y);

#define f251_x_plus_2y(z,x,y) f251_x_plus_c_times_y(z,x,2,y)
#define f251_x_plus_3y(z,x,y) f251_x_plus_c_times_y(z,x,3,y)
#define f251_x_plus_4y(z,x,y) f251_x_plus_c_times_y(z,x,4,y)

#define f251_x_minus_2y(z,x,y) f251_x_minus_c_times_y(z,x,2,y)
#define f251_x_minus_3y(z,x,y) f251_x_minus_c_times_y(z,x,3,y)
#define f251_x_minus_4y(z,x,y) f251_x_minus_c_times_y(z,x,4,y)

#else

void f251_x_plus_2y(felt_t z, const felt_t x, const felt_t y);
void f251_x_plus_3y(felt_t z, const felt_t x, const felt_t y);
void f251_x_plus_4y(felt_t z, const felt_t x, const felt_t y);

void f251_x_minus_2y(felt_t z, const felt_t x, const felt_t y);
void f251_x_minus_3y(felt_t z, const felt_t x, const felt_t y);
void f251_x_minus_4y(felt_t z, const felt_t x, const felt_t y);

#endif

////////////////////////////////////////////////////////////////////////////////
///  F251 sum state functions
////////////////////////////////////////////////////////////////////////////////

SYSV_ABI void f251_sum_state_3(felt_t z, const felt_t state[]);
SYSV_ABI void f251_sum_state_4(felt_t t1, felt_t t2, const felt_t state[]);
SYSV_ABI void f251_sum_state_5(felt_t t, const felt_t state[]);
SYSV_ABI void f251_sum_state_9(felt_t t1, felt_t t2, const felt_t state[]);

////////////////////////////////////////////////////////////////////////////////
///  F251 Montgomery functions 
////////////////////////////////////////////////////////////////////////////////

void f251_to_montgomery(felt_t mx, const felt_t x);
void f251_from_montgomery(felt_t x, const felt_t mx);
SYSV_ABI void f251_montgomery_mult(felt_t z, const felt_t x, const felt_t y);
void f251_montgomery_cube(felt_t z, const felt_t x);

#endif // __F251_H__
