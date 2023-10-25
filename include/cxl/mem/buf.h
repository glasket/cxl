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
#include <cxl/error.h>
#include <cxl/mem/alloc.h>
#include <cxl/result.h>
#include <cxl/type.h>
#include <stdlib.h>

#define CXL_TYPE u8 *
#define CXL_SUFFIX u8_ptr
#define CXL_DECL_ONLY 1
#include <cxl/gen/option.h>
#undef CXL_TYPE
#undef CXL_SUFFIX
#undef CXL_DECL_ONLY

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

XResult xbuf_grow(XBuffer *buf);

XResult xbuf_grow_until(XBuffer *buf, const usize cap);

XResult xbuf_grow_by(XBuffer *buf, const usize increase); // Equivalent to RawVec.Reserve

XResult xbuf_set_cap(XBuffer *buf, const usize cap);

usize xbuf_cap(const XBuffer *const buf);

usize xbuf_alignment(const XBuffer *const buf);

// TODO Maybe allow buf_realign?

XResult xbuf_access(XBuffer *const buf, const usize offset);

// Converts an existing pointer into a buffer, copies the data.
XResult xbuf_from_ptr(void *const ptr, const XLayout layout, const XAllocator *const alloc);

XOption_u8_ptr xbuf_ptr(XBuffer *const buf);

bool xbuf_check_alignment(const XBuffer *const buf, const XBuffer *const other);

#endif
