/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file buf.c
 * @brief Buffer type representing contiguous memory for CXL.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "ckdint.h"
#include "common.h"
#include <cxl/mem/buf.h>
#include <cxl/option.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

#define CXL_TYPE byte *
#define CXL_SUFFIX byte_ptr
#include <cxl/gen/result.h>

struct XBuffer {
  XAllocator *alloc;
  XLayout layout;
  byte mem[];
};

static XResult internal_xbuf_set_cap(XBuffer *buf, const usize cap) {
  if (cap == buf->layout.size) {
    return xres_ok(buf); // Setting size to what it already is
  }

  XResult res = buf->alloc->realloc(
      buf, buf->layout, (XLayout){.alignment = buf->layout.alignment, .size = cap}, sizeof(XBuffer)
  );
  if (res.is_err) {
    return res;
  }
  XBuffer *new_buffer = res.value.ok;
  if (new_buffer == nullptr) {
    return xres_err(X_ERR_ALLOC);
  }

  new_buffer->layout = buf->layout;
  new_buffer->alloc = buf->alloc;
  return xres_ok(new_buffer);
}

XResult xbuf_new(const XLayout layout, const XAllocator *const alloc) {
  if (layout.alignment == 0) {
    return xres_err(X_ERR_BAD_ALIGNMENT);
  }
  XResult res = alloc->alloc(layout, sizeof(XBuffer));
  if (res.is_err) {
    return res;
  }
  XBuffer *buf = res.value.ok;

  buf->layout = layout;
  // Casting to init the allocator pointer
  buf->alloc = (XAllocator *)alloc;
  return xres_ok(buf);
}

void xbuf_free(XBuffer *buf) {
  free(buf);
  buf = nullptr;
}

XResult xbuf_grow(XBuffer *buf) {
  return xbuf_grow_by(buf, buf->layout.size == 0 ? 1 : buf->layout.size);
}

XResult xbuf_grow_until(XBuffer *buf, const usize target_cap) {
  usize new_size = buf->layout.size;
  if (target_cap <= new_size) {
    return xres_ok(buf); // Already big enough
  }

  while (new_size < target_cap) { // TODO Better algorithm
    new_size *= 2;
  }

  return xbuf_grow_by(buf, target_cap - buf->layout.size);
}

XResult xbuf_grow_by(XBuffer *buf, const usize increase) {
  if (increase == 0) {
    return xres_ok(buf); // Grow by nothing is fine
  }

  usize new_cap = 0;
  if (ckd_add(&new_cap, buf->layout.size, increase)) {
    return xres_err(X_ERR_OVERFLOW);
  }

  return xbuf_set_cap(buf, new_cap);
}

XResult xbuf_set_cap(XBuffer *buf, const usize cap) {
  return internal_xbuf_set_cap(buf, cap);
}

usize xbuf_cap(const XBuffer *const buf) {
  return buf->layout.size;
}

usize xbuf_alignment(const XBuffer *const buf) {
  return buf->layout.alignment;
}

XResult_byte_ptr xbuf_access(XBuffer *const buf, const usize offset) {
  if (offset >= buf->layout.size) {
    return xres_err_byte_ptr(X_ERR_BOUNDS);
  }
  return xres_ok_byte_ptr(&buf->mem[offset * buf->layout.alignment]);
}

XResult xbuf_from_ptr(void *const ptr, const XLayout layout, const XAllocator *const alloc) {
  XResult res = xbuf_new(layout, alloc);
  if (res.is_err) {
    return res;
  }
  XBuffer *buf = res.value.ok;
  memcpy(buf->mem, ptr, layout.size * layout.alignment);
  return xres_ok(buf);
}

XOption_byte_ptr xbuf_ptr(XBuffer *const buf) {
  if (buf == nullptr || buf->layout.size == 0) {
    return xopt_none_byte_ptr();
  }
  return xopt_some_byte_ptr(buf->mem);
}

bool xbuf_check_alignment(const XBuffer *const buf, const XBuffer *const other) {
  return buf->layout.alignment == other->layout.alignment;
}
