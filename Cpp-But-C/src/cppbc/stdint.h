/**
 * C++ But C
 * Copyright (C) 2019  Martino Kuan
 *
 * This file is part of C++ But C.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CPPBC_STDINT_H_
#define CPPBC_STDINT_H_

#include <limits.h>
#include <stddef.h>

/*
 * Contributor warning: As with the rest of the library, this header may
 * only use C89/C90 features.  Compiler or language extensions, external
 * libraries, and new standard features are disallowed.
 *
 * This is NOT a standards conforming implementation of stdint.h, because
 * there are no definitions for 64-bit int, wint, and other important
 * requirements.  Certain features are left undefined, for architecture and
 * implementation independence purposes.  In addition, various standard
 * library headers are included for convenience when they shouldn't be
 * included.  Due to these discrepancies, this file should kept hidden from
 * the public API.
 *
 * The following standards-related considerations have been evaluated:
 * - C++20: Two's complement is the ONLY representation of signed integers,
 *          but this is ignored, as the latest C standard does not yet have
 *          the same requirement.
 */

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L

/*
 * Load the standard stdint.h if in C99 or C++11 mode.
 *
 * Contributor warning: You may ONLY use what is defined in the else case!
 * The inclusion is merely a convenience if the compiler implements C90,
 * which means that there is no need for duplicated work and the additional
 * define case, as specified below.
 */
#include <stdint.h>

#else

/*
 * Note: Define CPPBC_STDINT_SIGN_MAG_REP if your target architecture uses
 * sign-magnitude representation. Otherwise, you don't have to do anything.
 *
 * If your architecture is not listed here, define a macro for your
 * architecture through your compiler.  Then, insert a preprocessor check
 * that defines CPPBC_STDINT_SIGN_MAG_REP for your macro.
 *
 * Example:
 * #ifdef _8_BIT_SIGN_MAG_CPU_ARCH
 * #define CPPBC_STDINT_SIGN_MAG_REP
 * #endif
 */

/* Types */
typedef signed char int_least8_t;
typedef signed short int_least16_t;
typedef signed long int_least32_t;

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned long uint_least32_t;

#if defined(CPPBC_STDINT_SIGN_MAG_REP) /* Sign-magnitude */
#define CPPBC_STDINT_SIGNED_MIN(signed_type) ((signed_type) ~((signed_type) 0))
#else /* One's Complement and Two's Complement */
#define CPPBC_STDINT_SIGNED_MIN(signed_type) \
    ((signed_type) (((signed_type) ~((signed_type) 0)) << ((sizeof(signed_type) * CHAR_BIT) - 1)))
#endif

#define CPPBC_STDINT_SIGNED_MAX(signed_type) \
    ((signed_type) ~(((signed_type) ~((signed_type) 0)) << ((sizeof(signed_type) * CHAR_BIT) - 1)))
#define CPPBC_STDINT_UNSIGNED_MAX(unsigned_type) ((unsigned_type) ~((unsigned_type) 0))

/* Signed integer minimum values */
#define INT_LEAST8_MIN CPPBC_STDINT_SIGNED_MIN(int_least8_t)
#define INT_LEAST16_MIN CPPBC_STDINT_SIGNED_MIN(int_least16_t)
#define INT_LEAST32_MIN CPPBC_STDINT_SIGNED_MIN(int_least32_t)

/* Signed integer maximum values */
#define INT_LEAST8_MAX CPPBC_STDINT_SIGNED_MAX(int_least8_t)
#define INT_LEAST16_MAX CPPBC_STDINT_SIGNED_MAX(int_least16_t)
#define INT_LEAST32_MAX CPPBC_STDINT_SIGNED_MAX(int_least32_t)

/* Unsigned integer maximum values */
#define UINT_LEAST8_MAX CPPBC_STDINT_UNSIGNED_MAX(uint_least8_t)
#define UINT_LEAST16_MAX CPPBC_STDINT_UNSIGNED_MAX(uint_least16_t)
#define UINT_LEAST32_MAX CPPBC_STDINT_UNSIGNED_MAX(uint_least32_t)

/* Additional limit values */
#define SIZE_MAX CPPBC_STDINT_UNSIGNED_MAX(size_t)
#define PTRDIFF_MIN CPPBC_STDINT_SIGNED_MIN(ptrdiff_t)
#define PTRDIFF_MAX CPPBC_STDINT_SIGNED_MAX(ptrdiff_t)

/* Function macros */
#define INT8_C(value) ((int_least8_t) value)
#define INT16_C(value) ((int_least16_t) value)
#define INT32_C(value) ((int_least32_t) value)

#endif /* __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L */

#endif /* CPPBC_STDINT_H_ */
