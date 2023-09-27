/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file vec.h
 * @brief Generic vector implementation for wrapping.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_VEC_H
#define CXL_VEC_H
#include "mem.h"
#include <stddef.h>
#include <stdlib.h>

#define vec_new_of(type, capacity) vec_new(capacity, sizeof(type))

typedef struct Vec Vec;

typedef struct Slice Slice;

/**
 * @brief Create a new vector.
 * @param[in] cap the initial size of the vector.
 * @param[in] size the size of each element in the vector.
 * @return a pointer to the new vector.
 * @retval nullptr if memory allocation failed.
 */
Vec *vec_new(const size_t cap, const size_t size);

Vec *vec_new_zeroed(const size_t cap, const size_t size);

/**
 * @brief Free a vector.
 * @param[in] vec the vector to free.
 */
void vec_free(Vec *vec);

MemErr vec_reserve(Vec *vec, size_t additional);

MemErr vec_reserve_exact(Vec *vec, size_t cap);

MemErr vec_shrink(Vec *vec);

void *vec_get(Vec *vec, size_t idx);

void vec_set(Vec *vec, size_t idx, void *val);

#endif
