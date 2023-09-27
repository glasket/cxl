/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file mem.c
 * @brief Memory management utilities for CXL.
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

struct Buffer {
  const Allocator *const alloc;
  Layout layout;
  uint8_t mem[];
};

Buffer *buf_new(const Layout layout, const Allocator *const alloc) {
  if (layout.alignment == 0) {
    return nullptr;
  }
  Buffer *buf = alloc->alloc(layout, sizeof(Buffer));
  if (buf == nullptr) {
    return nullptr;
  }

  buf->layout = layout;
  // Casting to init the allocator pointer
  *((Allocator **)buf->alloc) = (Allocator *)alloc;
  return buf;
}

void buf_free(Buffer *buf) {
  if (buf == nullptr) {
    return;
  }
  free(buf);
  buf = nullptr;
}

MemErr buf_grow(Buffer *buf) {
  return buf_grow_by(buf, buf->layout.size == 0 ? 1 : buf->layout.size);
}

MemErr buf_grow_by(Buffer *buf, const size_t increase) {
  if (increase == 0) {
    return MEM_OK; // Grow by nothing is fine
  }

  size_t new_cap = 0;
  if (ckd_add(&new_cap, buf->layout.size, increase)) {
    return MEM_ERR_OVERFLOW;
  }

  return buf_set_cap(buf, new_cap);
}

MemErr buf_set_cap(Buffer *buf, const size_t cap) {
  if (cap == 0) {
    return MEM_ERR_INVALID_SET;
  }

  void *new_buffer =
      buf->alloc->realloc(buf, buf->layout, (Layout){.alignment = buf->layout.alignment, .size = cap}, sizeof(Buffer));
  if (new_buffer == nullptr) {
    return MEM_ERR_ALLOC;
  }

  buf = new_buffer;
  buf->layout.size = cap;
  return MEM_OK;
}

size_t buf_cap(const Buffer *const buf) {
  return buf->layout.size;
}

size_t buf_alignment(const Buffer *const buf) {
  return buf->layout.alignment;
}

void *buf_access(const Buffer *const buf, const size_t offset) {
  if (offset >= buf->layout.size) {
    return nullptr;
  }
  return (void *)&buf->mem[offset * buf->layout.alignment];
}

Buffer *buf_from_ptr(void *const ptr, const Layout layout, const Allocator *const alloc) {
  Buffer *buf = buf_new(layout, alloc);
  if (buf == nullptr) {
    return nullptr;
  }
  memcpy(buf->mem, ptr, layout.size * layout.alignment);
  return buf;
}

void *buf_ptr(const Buffer *const buf) {
  return (void *)buf->mem;
}
