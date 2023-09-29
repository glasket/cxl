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

typedef struct Buffer Buffer;

Buffer *buf_new(const Layout layout, const Allocator *const alloc);

/**
 * @brief Frees the buffer
 *
 * @param[in,out] buf The buffer to free. Set to nullptr after freeing.
 */
void buf_free(Buffer *buf);

MemErr buf_grow(Buffer *buf);

MemErr buf_grow_by(Buffer *buf, const size_t increase); // Equivalent to RawVec.Reserve

MemErr buf_set_cap(Buffer *buf, const size_t cap);

size_t buf_cap(const Buffer *const buf);

size_t buf_alignment(const Buffer *const buf);

// TODO Maybe allow buf_realign?

void *buf_access(const Buffer *const buf, const size_t offset);

// TODO
// Converts an existing pointer into a buffer, copies the data.
Buffer *buf_from_ptr(void *const ptr, const Layout layout, const Allocator *const alloc);

// Returns the pointer to the buffer's data. nullptr if the buffer is empty.
void *buf_ptr(const Buffer *const buf);

#endif
