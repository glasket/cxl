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
#include <stdint.h>
#include <string.h>

struct XBuffer {
  const XAllocator *const alloc;
  XLayout layout;
  uint8_t mem[];
};

XBuffer *xbuf_new(const XLayout layout, const XAllocator *const alloc) {
  if (layout.alignment == 0) {
    return nullptr;
  }
  XBuffer *buf = alloc->alloc(layout, sizeof(XBuffer));
  if (buf == nullptr) {
    return nullptr;
  }

  buf->layout = layout;
  // Casting to init the allocator pointer
  *((XAllocator **)buf->alloc) = (XAllocator *)alloc;
  return buf;
}

void xbuf_free(XBuffer *buf) {
  free(buf);
  buf = nullptr;
}

XMemErr xbuf_grow(XBuffer *buf) {
  return xbuf_grow_by(buf, buf->layout.size == 0 ? 1 : buf->layout.size);
}

XMemErr xbuf_grow_by(XBuffer *buf, const size_t increase) {
  if (increase == 0) {
    return MEM_OK; // Grow by nothing is fine
  }

  size_t new_cap = 0;
  if (ckd_add(&new_cap, buf->layout.size, increase)) {
    return MEM_ERR_OVERFLOW;
  }

  return xbuf_set_cap(buf, new_cap);
}

XMemErr xbuf_set_cap(XBuffer *buf, const size_t cap) {
  if (cap == buf->layout.size) {
    return MEM_OK; // Setting size to what it already is
  }

  void *new_buffer = buf->alloc->realloc(
      buf, buf->layout, (XLayout){.alignment = buf->layout.alignment, .size = cap}, sizeof(XBuffer)
  );
  if (new_buffer == nullptr) {
    return MEM_ERR_ALLOC;
  }

  buf = new_buffer;
  buf->layout.size = cap;
  return MEM_OK;
}

size_t xbuf_cap(const XBuffer *const buf) {
  return buf->layout.size;
}

size_t xbuf_alignment(const XBuffer *const buf) {
  return buf->layout.alignment;
}

void *xbuf_access(const XBuffer *const buf, const size_t offset) {
  if (offset >= buf->layout.size) {
    return nullptr;
  }
  return (void *)&buf->mem[offset * buf->layout.alignment];
}

XBuffer *xbuf_from_ptr(void *const ptr, const XLayout layout, const XAllocator *const alloc) {
  XBuffer *buf = xbuf_new(layout, alloc);
  if (buf == nullptr) {
    return nullptr;
  }
  memcpy(buf->mem, ptr, layout.size * layout.alignment);
  return buf;
}

void *xbuf_ptr(const XBuffer *const buf) {
  if (buf == nullptr || buf->layout.size == 0) {
    return nullptr;
  }
  return (void *)buf->mem;
}
