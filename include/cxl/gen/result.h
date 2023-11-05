/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#ifndef CXL_GEN_RESULT_H
#define CXL_GEN_RESULT_H
#include <assert.h>
#include <cxl/macros.h>
#include <stdint.h>
#endif

#if defined(CXL_TYPE)

#if defined(CXL_DECL_ONLY) && !defined(CXL_INCL_STRUCT) || defined(CXL_INCL_STRUCT)
// We include on declaration only because Results can be statically allocated.
#define XRES_INCL_STRUCT 1
#endif

#ifndef CXL_SUFFIX
#define XRES_SUFFIX
#else
#define XRES_SUFFIX CAT_H(_, CXL_SUFFIX)
#endif

#define XRES_NAME CAT_H(XResult, XRES_SUFFIX)
#define XRES_OK CAT_H(xres_ok, XRES_SUFFIX)
#define XRES_ERR CAT_H(xres_err, XRES_SUFFIX)
#define XRES_UNWRAP CAT_H(xres_unwrap, XRES_SUFFIX)
#define XRES_UNWRAP_OR CAT_H(xres_unwrap_or, XRES_SUFFIX)
#define XRES_UNWRAP_OR_ELSE CAT_H(xres_unwrap_or_else, XRES_SUFFIX)
#define XRES_UNWRAP_UNCHECKED CAT_H(xres_unwrap_unchecked, XRES_SUFFIX)

#ifdef XRES_INCL_STRUCT
typedef struct XRES_NAME {
  union {
    CXL_TYPE ok;
    uintptr_t err;
  } value;
  bool is_err;
  bool is_ok;
} XRES_NAME;
#endif

#ifdef CXL_DECL_ONLY

XRES_NAME XRES_OK(CXL_TYPE val);
XRES_NAME XRES_ERR(uintptr_t err);

CXL_TYPE XRES_UNWRAP(XRES_NAME res);
CXL_TYPE XRES_UNWRAP_OR(XRES_NAME res, CXL_TYPE def);
CXL_TYPE XRES_UNWRAP_OR_ELSE(XRES_NAME res, CXL_TYPE (*const f)(uintptr_t err));

CXL_TYPE XRES_UNWRAP_UNCHECKED(XRES_NAME res);

#else

XRES_NAME XRES_OK(CXL_TYPE val) {
  return (XRES_NAME){.value.ok = val, .is_err = false, .is_ok = true};
}
XRES_NAME XRES_ERR(uintptr_t err) {
  return (XRES_NAME){.value.err = err, .is_err = true, .is_ok = false};
}

CXL_TYPE XRES_UNWRAP(XRES_NAME res) {
  assert(res.is_ok);
  if (res.is_ok) {
    return res.value.ok;
  }
  return EMPTY_INIT(CXL_TYPE);
}
CXL_TYPE XRES_UNWRAP_OR(XRES_NAME res, CXL_TYPE def) {
  if (res.is_ok) {
    return res.value.ok;
  }
  return def;
}
CXL_TYPE XRES_UNWRAP_OR_ELSE(XRES_NAME res, CXL_TYPE (*const f)(uintptr_t err)) {
  if (res.is_ok) {
    return res.value.ok;
  }
  return f(res.value.err);
}

CXL_TYPE XRES_UNWRAP_UNCHECKED(XRES_NAME res) {
  return res.value.ok;
}

#endif

#undef XRES_NAME
#undef XRES_OK
#undef XRES_ERR
#undef XRES_UNWRAP
#undef XRES_UNWRAP_OR
#undef XRES_UNWRAP_OR_ELSE
#undef XRES_UNWRAP_UNCHECKED
#undef XRES_INCL_STRUCT
#undef CXL_INCL_STRUCT
#undef CXL_TYPE
#undef CXL_SUFFIX
#undef XRES_SUFFIX
#undef CXL_DECL_ONLY

#else
#error "Must define CXL_TYPE before including this file."
#endif
