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
#include <cxl/mem/buf.h>
#include <cxl/vec.h>
#include <string.h>

static XVec internal_vec_new(const size_t cap, const size_t elem_size, const XAllocator *const alloc) {
  return (XVec){.buf = xres_unwrap(xbuf_new((XLayout){.size = cap, .alignment = elem_size}, alloc)), .len = 0};
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

XErr xvec_reserve(XVec *vec, size_t additional) {
  return xbuf_grow_by(&vec->buf, additional);
}

XErr xvec_reserve_exact(XVec *vec, size_t cap) {
  if (cap < vec->len) {
    return X_ERR_BAD_SHRINK;
  }
  return xbuf_set_cap(&vec->buf, cap);
}

XErr xvec_shrink(XVec *vec) {
  return xbuf_set_cap(&vec->buf, vec->len);
}

XResult xvec_get(XVec *vec, size_t idx) {
  if (idx > vec->len) {
    return xres_err(X_ERR_BOUNDS);
  }
  return xbuf_access(vec->buf, idx);
}

XErr xvec_set(XVec *vec, size_t idx, void *val) {
  if (idx > vec->len) {
    return X_ERR_BOUNDS;
  }
  // Already checked that idx is in bounds above
  void *mem = xres_unwrap_unchecked(xbuf_access(vec->buf, idx));
  memcpy(mem, val, xbuf_alignment(vec->buf));
  return X_OK;
}

XErr xvec_push(XVec *vec, void *val) {
  if (vec->len == xbuf_cap(vec->buf)) {
    XErr res = xbuf_grow(&vec->buf);
    if (xerr_is_err(res)) {
      return res;
    }
  }
  // Don't need to check for success, len is always <= cap
  void *mem = xres_unwrap_unchecked(xbuf_access(vec->buf, vec->len));
  memcpy(mem, val, xbuf_alignment(vec->buf));
  vec->len += 1;
  return X_OK;
}

XResult xvec_pop(XVec *vec) {
  if (vec->len == 0) {
    return xres_err(X_ERR_EMPTY);
  }
  // len is always <= cap, so len can decrease w/o checking for success first
  vec->len -= 1;
  return xbuf_access(vec->buf, vec->len);
}

size_t xvec_cap(XVec vec) {
  return xbuf_cap(vec.buf);
}

size_t xvec_len(XVec vec) {
  return vec.len;
}
