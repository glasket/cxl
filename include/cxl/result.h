/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file result.h
 * @brief Result type representing a value that can either be a value or an error.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_RESULT_H
#define CXL_RESULT_H
#include <stdint.h>

typedef struct XResult {
  union {
    void *ok;
    uintptr_t err; // uintptr_t so it aligns with void*
  } value;
  bool is_err;
  bool is_ok;
} XResult;

XResult xres_ok(void *ptr);
XResult xres_err(uintptr_t err);

void *xres_unwrap(XResult res);
void *xres_unwrap_or(XResult res, void * or);
void *xres_unwrap_or_else(XResult res, void *(*const f)(uintptr_t err));

void *xres_unwrap_unchecked(XResult res);

#endif
