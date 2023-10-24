/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file alloc.h
 * @brief Allocators.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_MEM_ALLOC_H
#define CXL_MEM_ALLOC_H

#include <cxl/result.h>
#include <cxl/type.h>
#include <stddef.h>

#define XLAYOUT_INIT(layout_size, layout_alignment) \
  (XLayout) { \
    .size = layout_size, .alignment = layout_alignment \
  }

typedef struct XLayout {
  usize size;
  usize alignment;
} XLayout;

/**
 * @brief Allocates a new buffer with the specified layout.
 *
 * @param[in] layout The layout of the buffer to allocate.
 *
 * @return Pointer to the allocated buffer.
 * @retval nullptr if allocation failed.
 */
typedef XResult (*const cxl_mem_allocate)(const XLayout layout, const usize pad);

/**
 * @brief Reallocates a buffer with the specified layout.
 *
 * @param[in] ptr Pointer to the buffer to reallocate.
 * @param[in] old_layout The layout of the buffer before reallocation. Useful if zeroing.
 * @param[in] new_layout The layout of the buffer after reallocation.
 *
 * @return Pointer to the reallocated buffer.
 * @retval nullptr if reallocation failed.
 */
typedef XResult (*const cxl_mem_reallocate)(
    void *const ptr, const XLayout old_layout, const XLayout new_layout, const usize pad
);

/**
 * @brief Deallocates a buffer.
 *
 * @param[in] buf Pointer to the buffer to deallocate.
 * @param[in] full_size The full size of the buffer. For zeroing.
 */
typedef void (*const cxl_mem_deallocate)(void *const buf, const usize full_size);

typedef struct XAllocator {
  cxl_mem_allocate alloc;
  cxl_mem_reallocate realloc;
  cxl_mem_deallocate free;
} XAllocator;

// TODO Maybe rewrite cxl_mem_allocate to be more like calloc API?
// This would help when implementing NodeList since it would assist with limiting
// fragmentation and the number of alloc calls. i.e. the allocator could try to
// allocate N nodes of size sizeof(Node) and if the allocator is non-contiguous
// it could notify the nodelist how many nodes were allocated so that it can
// attempt to allocate the remaining nodes again.
// Buffer would of course just use alloc(1, XLayout, pad).
// (NodeList is a planned memory representation for non-contiguous allocators, like
// linked block arenas.)

XResult balloc(const XLayout layout, const usize pad);
XResult zballoc(const XLayout layout, const usize pad);

XResult brealloc(void *const ptr, const XLayout old_layout, const XLayout new_layout, const usize pad);
XResult zbrealloc(void *const ptr, const XLayout old_layout, const XLayout new_layout, const usize pad);

void bfree(void *const ptr, const usize full_size);
void zbfree(void *const ptr, const usize full_size);

extern const XAllocator GlobalAllocator;

// Also does overflow checks
extern const XAllocator ZeroAllocator;

#endif
