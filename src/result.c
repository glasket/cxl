/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file result.c
 * @brief Result type representing a value that can either be a value or an error.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include <assert.h>
#include <cxl/result.h>

XResult xres_ok(void *ptr) {
  return (XResult){.res.ptr = ptr, .is_err = false, .is_ok = true};
}

XResult xres_err(uintptr_t err) {
  return (XResult){.res.err = err, .is_err = true, .is_ok = false};
}

void *xres_unwrap(XResult res) {
  assert(res.is_ok);
  if (res.is_ok) {
    return res.res.ptr;
  }
  return nullptr;
}

void *xres_unwrap_or(XResult res, void *def) {
  if (res.is_ok) {
    return res.res.ptr;
  }
  return def;
}

void *xres_unwrap_or_else(XResult res, void *(*or_else)(uintptr_t err)) {
  if (res.is_ok) {
    return res.res.ptr;
  }
  return or_else(res.res.err);
}

void *xres_unwrap_unchecked(XResult res) {
  return res.res.ptr;
}

XOption xres_get_ok(XResult res) {
  if (res.is_ok) {
    return xopt_some(res.res.ptr);
  }
  return xopt_none();
}

XOption xres_get_err(XResult res) {
  if (res.is_err) {
    return xopt_some((void *)res.res.err);
  }
  return xopt_none();
}
