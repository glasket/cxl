/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file type.h
 * @brief Common typedefs for CXL.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_TYPE_H
#define CXL_TYPE_H

#include <stddef.h>
#include <stdint.h>
#include <uchar.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef char byte;

typedef char8_t c8;
typedef char16_t c16;
typedef char32_t c32;

typedef float f32;
typedef double f64;

typedef size_t usize;
typedef ptrdiff_t isize;

#endif
