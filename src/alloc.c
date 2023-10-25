/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file alloc.c
 * @brief Allocators.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "auto.h"
#include "ckdint.h"
#include <cxl/error.h>
#include <cxl/mem/alloc.h>
#include <cxl/type.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CXL_TYPE usize
#define CXL_SUFFIX usize
#define CXL_INCL_STRUCT 1
#include <cxl/gen/result.h>
#undef CXL_INCL_STRUCT
#undef CXL_TYPE
#undef CXL_SUFFIX

static XResult_usize layout_size(const XLayout layout, const usize pad) {
  if (layout.size == 0 || layout.alignment == 0) {
    return xres_err_usize(X_ERR_BAD_SIZE);
  }

  usize total = 0;
  if (ckd_mul(&total, layout.size, layout.alignment) || ckd_add(&total, total, pad)) {
    return xres_err_usize(X_ERR_OVERFLOW);
  }

  return xres_ok_usize(total);
}

static bool layout_eq(const XLayout a, const XLayout b) {
  return a.size == b.size && a.alignment == b.alignment;
}

XResult balloc(const XLayout layout, const usize pad) {
  var size = layout_size(layout, pad);
  if (size.is_err) {
    return xres_err(size.value.err);
  }
  void *alloc = malloc(size.value.ok);
  if (alloc == nullptr) {
    return xres_err(X_ERR_ALLOC);
  }
  return xres_ok(alloc);
}

XResult zballoc(const XLayout layout, const usize pad) {
  var size = layout_size(layout, pad);
  if (size.is_err) {
    return xres_err(size.value.err);
  }
  void *alloc = calloc(1, size.value.ok);
  if (alloc == nullptr) {
    return xres_err(X_ERR_ALLOC);
  }
  return xres_ok(alloc);
}

XResult brealloc(void *const ptr, const XLayout old_layout, const XLayout new_layout, const usize pad) {
  assert(ptr != nullptr);
  if (layout_eq(old_layout, new_layout)) {
    return xres_ok(ptr);
  }

  var res = layout_size(new_layout, pad);
  if (res.is_err) {
    return xres_err(res.value.err);
  }

  void *alloc = realloc(ptr, res.value.ok);
  if (alloc == nullptr) {
    return xres_err(X_ERR_ALLOC);
  }
  return xres_ok(alloc);
}

XResult zbrealloc(void *const ptr, const XLayout old_layout, const XLayout new_layout, const usize pad) {
  assert(ptr != nullptr);
  if (layout_eq(old_layout, new_layout)) {
    return xres_ok(ptr);
  }

  var res = layout_size(new_layout, pad);
  if (res.is_err) {
    return xres_err(res.value.err);
  }

  // Old size can't overflow.
  usize old_size = old_layout.size * old_layout.alignment + pad;
  usize new_size = res.value.ok;

  void *new_alloc = malloc(new_size); // Not calloc because we memcpy anyways
  if (new_alloc == nullptr) {
    return xres_err(X_ERR_ALLOC);
  }

  if (new_size < old_size) {
    memcpy(new_alloc, ptr, new_size);
    zbfree(ptr, old_size);
    return xres_ok(new_alloc);
  }

  memcpy(new_alloc, ptr, old_size);
  memset((u8 *)new_alloc + old_size, 0, new_size - old_size);
  zbfree(ptr, old_size);
  return xres_ok(new_alloc);
}

void bfree(void *const ptr, [[maybe_unused]] const usize) {
  free(ptr);
}

void zbfree(void *const ptr, const usize full_size) {
  memset(ptr, 0, full_size);
  free(ptr);
}

const XAllocator GlobalAllocator = {
    .alloc = balloc,
    .realloc = brealloc,
    .free = bfree,
};

const XAllocator ZeroAllocator = {
    .alloc = zballoc,
    .realloc = zbrealloc,
    .free = zbfree,
};
