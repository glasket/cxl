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

#pragma once
#ifndef CXL_GEN_OPTION_H
#define CXL_GEN_OPTION_H
#include <assert.h>
#include <cxl/macros.h>

#define CXL_GEN_OPTION(TYPE, SUFFIX) \
  typedef struct XOption_##SUFFIX { \
    TYPE data; \
    bool is_some; \
    bool is_none; \
  } XOption_##SUFFIX; \
\
  XOption_##SUFFIX xopt_none_##SUFFIX(void) { \
    return (XOption_##SUFFIX){.is_none = true, .is_some = false, .data = EMPTY_INIT(TYPE)}; \
  } \
\
  XOption_##SUFFIX xopt_some_##SUFFIX(TYPE val) { \
    return (XOption_##SUFFIX){.is_none = false, .is_some = true, .data = val}; \
  } \
\
  TYPE xopt_unwrap_##SUFFIX(XOption_##SUFFIX opt) { \
    assert(opt.is_some); \
    if (opt.is_some) { \
      return opt.data; \
    } \
    return EMPTY_INIT(TYPE); \
  } \
  TYPE xopt_unwrap_or_##SUFFIX(XOption_##SUFFIX opt, TYPE def) { \
    if (opt.is_some) { \
      return opt.data; \
    }; \
    return def; \
  } \
  TYPE xopt_unwrap_or_else_##SUFFIX(XOption_##SUFFIX opt, TYPE (*const f)(void)) { \
    if (opt.is_some) { \
      return opt.data; \
    } \
    return f(); \
  }

#endif
