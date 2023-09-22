/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file ckdint.h
 * @brief Ensures that arithmetic overflow functions are defined for the current compiler.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#ifdef __has_include
#if __has_include("<stdckdint.h>")
#include <stdckdint.h>
#define CKDINT_IMPL_EXISTS 1
#endif
#endif

#if !defined CKDINT_IMPL_EXISTS && __has_builtin(__builtin_add_overflow) && __has_builtin(__builtin_mul_overflow) &&   \
    __has_builtin(__builtin_sub_overflow)
#define CKDINT_IMPL_EXISTS 1
#define ckd_add(result, a, b) __builtin_add_overflow(a, b, result)
#define ckd_mul(result, a, b) __builtin_mul_overflow(a, b, result)
#define ckd_sub(result, a, b) __builtin_sub_overflow(a, b, result)
#endif

#if !defined CKDINT_IMPL_EXISTS
#error "No implementation of ckdint found. Please use a compiler that has builtins or implements stdckdint."
#endif
