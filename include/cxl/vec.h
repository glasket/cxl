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
#include <cxl/error.h>
#include <cxl/mem/buf.h>
#include <stddef.h>
#include <stdlib.h>

// TODO Generic vector
// TODO Full vector impl

#define XVEC_INIT(vec_type, vec_cap) \
  ((XVec){.buf = xres_unwrap(xbuf_new(XLAYOUT_INIT(vec_cap, sizeof(vec_type)), &GlobalAllocator))})

#define XVEC_INIT_ALLOC(vec_type, vec_cap, vec_allocator) \
  ((XVec){.buf = xres_unwrap(xbuf_new(XLAYOUT_INIT(vec_cap, sizeof(vec_type)), vec_allocator))})

typedef struct XVec {
  XBuffer *buf;
  usize len;
} XVec;

/**
 * @brief Create a new vector.
 * @param[in] cap the initial size of the vector.
 * @param[in] size the size of each element in the vector.
 * @return the new vector.
 */
XVec xvec_new(const usize cap, const usize elem_size);

XVec xvec_new_with_alloc(const usize cap, const usize elem_size, const XAllocator *const alloc);

/**
 * @brief Free a vector.
 * @param[in] vec the vector to free.
 */
void xvec_free(XVec *vec);

XErr xvec_reserve(XVec *const vec, const usize additional);

XErr xvec_reserve_exact(XVec *const vec, const usize cap);

XErr xvec_shrink(XVec *const vec);

XResult xvec_get(const XVec *const vec, const usize idx);

XErr xvec_set(const XVec *const vec, const usize idx, const void *const val);

XErr xvec_push(XVec *const vec, const void *const val);

XResult xvec_pop(XVec *const vec);

XErr xvec_insert(XVec *const vec, const usize idx, const void *const val);

XErr xvec_append(XVec *const vec, const XVec other);

XErr xvec_append_raw(XVec *const vec, const void *const data, const usize data_elem_count);

void xvec_clear(XVec *const vec);

bool xvec_is_empty(const XVec vec);

usize xvec_cap(const XVec vec);

#endif
