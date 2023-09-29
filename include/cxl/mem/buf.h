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
#include "alloc.h"
#include <stdlib.h>

typedef struct XBuffer XBuffer;

XBuffer *xbuf_new(const XLayout layout, const XAllocator *const alloc);

/**
 * @brief Frees the buffer
 *
 * @param[in,out] buf The buffer to free. Set to nullptr after freeing.
 */
void xbuf_free(XBuffer *buf);

XMemErr xbuf_grow(XBuffer *buf);

XMemErr xbuf_grow_by(XBuffer *buf, const size_t increase); // Equivalent to RawVec.Reserve

XMemErr xbuf_set_cap(XBuffer *buf, const size_t cap);

size_t xbuf_cap(const XBuffer *const buf);

size_t xbuf_alignment(const XBuffer *const buf);

// TODO Maybe allow buf_realign?

void *xbuf_access(const XBuffer *const buf, const size_t offset);

// Converts an existing pointer into a buffer, copies the data.
XBuffer *xbuf_from_ptr(void *const ptr, const XLayout layout, const XAllocator *const alloc);

// Returns the pointer to the buffer's data. nullptr if the buffer is empty.
void *xbuf_ptr(const XBuffer *const buf);

#endif
