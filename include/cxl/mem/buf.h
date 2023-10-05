/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file buf.h
 * @brief Buffer type representing contiguous memory for CXL.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_MEM_BUF_H
#define CXL_MEM_BUF_H
#include "../error.h"
#include "../result.h"
#include "alloc.h"
#include <stdlib.h>

/**
 * @brief Buffer type that represents a contiguous block of memory.
 *
 * @details Undeyling representation is a pointer to a set of allocator functions,
 * a @ref XLayout "Layout", and a flexible array member representing the data.
 */
typedef struct XBuffer XBuffer;

XResult xbuf_new(const XLayout layout, const XAllocator *const alloc);

/**
 * @brief Frees the buffer
 *
 * @param[in,out] buf The buffer to free. Set to nullptr after freeing.
 */
void xbuf_free(XBuffer *buf);

XErr xbuf_grow(XBuffer **buf);

XErr xbuf_grow_by(XBuffer **buf, const size_t increase); // Equivalent to RawVec.Reserve

XErr xbuf_set_cap(XBuffer **buf, const size_t cap);

size_t xbuf_cap(const XBuffer *const buf);

size_t xbuf_alignment(const XBuffer *const buf);

// TODO Maybe allow buf_realign?

XResult xbuf_access(XBuffer *const buf, const size_t offset);

// Converts an existing pointer into a buffer, copies the data.
XResult xbuf_from_ptr(void *const ptr, const XLayout layout, const XAllocator *const alloc);

// Returns the pointer to the buffer's data. nullptr if the buffer is empty.
XOption xbuf_ptr(XBuffer *const buf);

#endif
