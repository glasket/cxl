/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file vec.c
 * @brief UTF-8 string types and function declarations.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "common.h"
#include <cxl/mem/alloc.h>
#include <cxl/mem/buf.h>
#include <cxl/vec.h>
#include <string.h>

struct XVec {
  XBuffer *buf;
  size_t len;
};

static XVec internal_vec_new(const size_t cap, const size_t elem_size, const XAllocator *const alloc) {
  return (XVec){.buf = xbuf_new((XLayout){.size = cap, .alignment = elem_size}, alloc), .len = 0};
}

XVec xvec_new(const size_t cap, const size_t elem_size) {
  return internal_vec_new(cap, elem_size, &GlobalAllocator);
}

XVec xvec_new_with_alloc(const size_t cap, const size_t elem_size, const XAllocator *const alloc) {
  return internal_vec_new(cap, elem_size, alloc);
}

void vec_free(XVec vec) {
  xbuf_free(vec.buf);
  vec.buf = nullptr;
}

XMemErr xvec_reserve(XVec *vec, size_t additional) {
  return xbuf_grow_by(vec->buf, additional);
}

XMemErr xvec_reserve_exact(XVec *vec, size_t cap) {
  if (cap < vec->len) {
    return MEM_ERR_INVALID_SHRINK;
  }
  return xbuf_set_cap(vec->buf, cap);
}

XMemErr xvec_shrink(XVec *vec) {
  return xbuf_set_cap(vec->buf, vec->len);
}

void *xvec_get(XVec *vec, size_t idx) {
  if (idx > vec->len) {
    return nullptr;
  }
  return xbuf_access(vec->buf, idx);
}

XMemErr xvec_set(XVec *vec, size_t idx, void *val) {
  if (idx > vec->len) {
    return MEM_ERR_OOB;
  }
  memcpy(xbuf_access(vec->buf, idx), val, xbuf_alignment(vec->buf));
  return MEM_OK;
}

XMemErr xvec_push(XVec *vec, void *val) {
  if (vec->len == xbuf_cap(vec->buf)) {
    XMemErr err = xbuf_grow(vec->buf);
    if (err) {
      return err;
    }
  }
  xbuf_access(vec->buf, vec->len);
  vec->len += 1;
}

void *xvec_pop(XVec *vec) {
  if (vec->len == 0) {
    return nullptr;
  }
  vec->len -= 1;
  return xbuf_access(vec->buf, vec->len);
}

size_t xvec_cap(XVec vec) {
  return xbuf_cap(vec.buf);
}

size_t xvec_len(XVec vec) {
  return vec.len;
}
