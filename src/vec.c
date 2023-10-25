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
#include <cxl/error.h>
#include <cxl/mem/buf.h>
#include <cxl/vec.h>
#include <string.h>

static XVec internal_vec_new(const usize cap, const usize elem_size, const XAllocator *const alloc) {
  return (XVec){.buf = xres_unwrap(xbuf_new((XLayout){.size = cap, .alignment = elem_size}, alloc)), .len = 0};
}

XVec xvec_new(const usize cap, const usize elem_size) {
  return internal_vec_new(cap, elem_size, &GlobalAllocator);
}

XVec xvec_new_with_alloc(const usize cap, const usize elem_size, const XAllocator *const alloc) {
  return internal_vec_new(cap, elem_size, alloc);
}

void vec_free(XVec vec) {
  xbuf_free(vec.buf);
  vec.buf = nullptr;
}

XErr xvec_reserve(XVec *const vec, const usize additional) {
  XResult res = xbuf_grow_by(vec->buf, additional);
  if (res.is_err) {
    return res.value.err;
  }
  vec->buf = res.value.ok;
  return X_OK;
}

XErr xvec_reserve_exact(XVec *const vec, const usize cap) {
  if (cap < vec->len) {
    return X_ERR_BAD_SHRINK;
  }
  XResult res = xbuf_set_cap(vec->buf, cap);
  if (res.is_err) {
    return res.value.err;
  }
  vec->buf = res.value.ok;
  return X_OK;
}

XErr xvec_shrink(XVec *const vec) {
  return xvec_reserve_exact(vec, vec->len);
}

XResult xvec_get(const XVec *const vec, usize idx) {
  if (idx > vec->len) {
    return xres_err(X_ERR_BOUNDS);
  }
  return xbuf_access(vec->buf, idx);
}

XErr xvec_set(const XVec *const vec, const usize idx, const void *const val) {
  if (idx > vec->len) {
    return X_ERR_BOUNDS;
  }
  // Already checked that idx is in bounds above
  void *mem = xres_unwrap_unchecked(xbuf_access(vec->buf, idx));
  memcpy(mem, val, xbuf_alignment(vec->buf));
  return X_OK;
}

XErr xvec_push(XVec *const vec, const void *const val) {
  if (vec->len == xbuf_cap(vec->buf)) {
    XResult res = xbuf_grow(vec->buf);
    if (res.is_err) {
      return res.value.err;
    }
  }
  // Don't need to check for success, len is always <= cap
  void *mem = xres_unwrap_unchecked(xbuf_access(vec->buf, vec->len));
  memcpy(mem, val, xbuf_alignment(vec->buf));
  vec->len += 1;
  return X_OK;
}

XResult xvec_pop(XVec *const vec) {
  if (vec->len == 0) {
    return xres_err(X_ERR_EMPTY);
  }
  // len is always <= cap, so len can decrease w/o checking for success first
  vec->len -= 1;
  return xbuf_access(vec->buf, vec->len);
}

static XErr internal_xvec_check_vec_align(const XVec vec, const XVec other) {
  if (xbuf_check_alignment(vec.buf, other.buf)) {
    return X_ERR_MISMATCHED_ALIGNMENT;
  }
  return X_OK;
}

XErr xvec_append(XVec *const vec, const XVec other) {
  XErr err = internal_xvec_check_vec_align(*vec, other);
  if (xerr_is_err(err)) {
    return err;
  }
  return xvec_append_raw(vec, xopt_unwrap_u8_ptr(xbuf_ptr(other.buf)), other.len);
}

// Assumes that the alignment of the vec elements is the same as the alignment of the data
XErr xvec_append_raw(XVec *const vec, const void *const data, const usize data_elem_count) {
  xbuf_grow_until(vec->buf, vec->len + data_elem_count);
  memcpy(xopt_unwrap_u8_ptr(xbuf_ptr(vec->buf)) + vec->len, data, data_elem_count * xbuf_alignment(vec->buf));
  vec->len += data_elem_count;
  return X_OK;
}

usize xvec_cap(const XVec vec) {
  return xbuf_cap(vec.buf);
}
