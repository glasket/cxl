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

// General guard
#ifndef CXL_GEN_OPTION_H
#define CXL_GEN_OPTION_H
#include <assert.h>
#include <cxl/macros.h>
#endif

#if defined(CXL_TYPE)

#if defined(CXL_DECL_ONLY) && !defined(CXL_INCL_STRUCT) || defined(CXL_INCL_STRUCT)
// We include on declaration only because Options can be statically allocated.
#define XOPT_INCL_STRUCT 1
#endif

#ifndef CXL_SUFFIX
#define XOPT_SUFFIX
#else
#define XOPT_SUFFIX CAT_H(_, CXL_SUFFIX)
#endif

#define XOPT_NAME CAT_H(XOption, XOPT_SUFFIX)
#define XOPT_NONE CAT_H(xopt_none, XOPT_SUFFIX)
#define XOPT_SOME CAT_H(xopt_some, XOPT_SUFFIX)
#define XOPT_UNWRAP CAT_H(xopt_unwrap, XOPT_SUFFIX)
#define XOPT_UNWRAP_OR CAT_H(xopt_unwrap_or, XOPT_SUFFIX)
#define XOPT_UNWRAP_OR_ELSE CAT_H(xopt_unwrap_or_else, XOPT_SUFFIX)

#ifdef XOPT_INCL_STRUCT
typedef struct XOPT_NAME {
  CXL_TYPE data;
  bool is_some;
  bool is_none;
} XOPT_NAME;
#endif

#ifdef CXL_DECL_ONLY

XOPT_NAME XOPT_NONE(void);

XOPT_NAME XOPT_SOME(CXL_TYPE val);

CXL_TYPE XOPT_UNWRAP(XOPT_NAME opt);
CXL_TYPE XOPT_UNWRAP_OR(XOPT_NAME opt, CXL_TYPE def);
CXL_TYPE XOPT_UNWRAP_OR_ELSE(XOPT_NAME opt, CXL_TYPE (*const f)(void));

#else

XOPT_NAME XOPT_NONE(void) {
  return (XOPT_NAME){.is_none = true, .is_some = false, .data = EMPTY_INIT(CXL_TYPE)};
}

XOPT_NAME XOPT_SOME(CXL_TYPE val) {
  return (XOPT_NAME){.is_none = false, .is_some = true, .data = val};
}

CXL_TYPE XOPT_UNWRAP(XOPT_NAME opt) {
  assert(opt.is_some);
  if (opt.is_some) {
    return opt.data;
  }
  return EMPTY_INIT(CXL_TYPE);
}
CXL_TYPE XOPT_UNWRAP_OR(XOPT_NAME opt, CXL_TYPE def) {
  if (opt.is_some) {
    return opt.data;
  };
  return def;
}
CXL_TYPE XOPT_UNWRAP_OR_ELSE(XOPT_NAME opt, CXL_TYPE (*const f)(void)) {
  if (opt.is_some) {
    return opt.data;
  }
  return f();
}

#endif

#undef XOPT_NAME
#undef XOPT_NONE
#undef XOPT_SOME
#undef XOPT_UNWRAP
#undef XOPT_UNWRAP_OR
#undef XOPT_UNWRAP_OR_ELSE
#undef XOPT_INCL_STRUCT
#undef CXL_INCL_STRUCT
#undef CXL_TYPE
#undef CXL_SUFFIX
#undef XOPT_SUFFIX
#undef CXL_DECL_ONLY

#else
#error "Must define CXL_TYPE before including this file."
#endif
