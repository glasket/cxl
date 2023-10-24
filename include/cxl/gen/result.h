
#pragma once
#ifndef CXL_GEN_RESULT_H
#define CXL_GEN_RESULT_H
#include <assert.h>
#include <cxl/gen/option.h>
#include <stdint.h>

#define CXL_GEN_RESULT(TYPE, SUFFIX) \
  CXL_GEN_OPTION(TYPE, SUFFIX) \
  typedef struct XResult_##SUFFIX { \
    union { \
      TYPE ok; \
      uintptr_t err; \
    } value; \
    bool is_err; \
    bool is_ok; \
  } XResult_##SUFFIX; \
\
  XResult_##SUFFIX xres_ok_##SUFFIX(TYPE val) { \
    return (XResult_##SUFFIX){.value.ok = val, .is_err = false, .is_ok = true}; \
  } \
  XResult_##SUFFIX xres_err_##SUFFIX(uintptr_t err) { \
    return (XResult_##SUFFIX){.value.err = err, .is_err = true, .is_ok = false}; \
  } \
\
  TYPE xres_unwrap_##SUFFIX(XResult_##SUFFIX res) { \
    assert(res.is_ok); \
    if (res.is_ok) { \
      return res.value.ok; \
    } \
    return EMPTY_INIT(TYPE); \
  } \
  TYPE xres_unwrap_or_##SUFFIX(XResult_##SUFFIX res, TYPE def) { \
    if (res.is_ok) { \
      return res.value.ok; \
    } \
    return def; \
  } \
  TYPE xres_unwrap_or_else_##SUFFIX(XResult_##SUFFIX res, TYPE (*const f)(uintptr_t err)) { \
    if (res.is_ok) { \
      return res.value.ok; \
    } \
    return f(res.value.err); \
  } \
\
  TYPE xres_unwrap_unchecked_##SUFFIX(XResult_##SUFFIX res) { \
    return res.value.ok; \
  }

#endif
