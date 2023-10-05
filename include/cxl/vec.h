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
#include "error.h"
#include "mem/alloc.h"
#include "result.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct XVec XVec;

typedef struct XSlice XSlice;

/**
 * @brief Create a new vector.
 * @param[in] cap the initial size of the vector.
 * @param[in] size the size of each element in the vector.
 * @return a pointer to the new vector.
 * @retval nullptr if memory allocation failed.
 */
XVec xvec_new(const size_t cap, const size_t elem_size);

XVec xvec_new_with_alloc(const size_t cap, const size_t elem_size, const XAllocator *const alloc);

/**
 * @brief Free a vector.
 * @param[in] vec the vector to free.
 */
void xvec_free(XVec *vec);

XErr xvec_reserve(XVec *vec, size_t additional);

XErr xvec_reserve_exact(XVec *vec, size_t cap);

XErr xvec_shrink(XVec *vec);

XResult xvec_get(XVec *vec, size_t idx);

XErr xvec_set(XVec *vec, size_t idx, void *val);

XErr xvec_push(XVec *vec, void *val);

XResult xvec_pop(XVec *vec);

size_t xvec_cap(XVec vec);

size_t xvec_len(XVec vec);

#endif
