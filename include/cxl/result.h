
#pragma once
#ifndef CXL_RESULT_H
#define CXL_RESULT_H

#include "option.h"
#include <stddef.h>
#include <stdint.h>

typedef struct XResult {
  union {
    void *ptr;
    uintptr_t err; // uintptr_t so it aligns with void*
  } res;
  bool is_err;
  bool is_ok;
} XResult;

XResult xres_ok(void *ptr);
XResult xres_err(uintptr_t err);

void *xres_unwrap(XResult res);
void *xres_unwrap_or(XResult res, void * or);
void *xres_unwrap_or_else(XResult res, void *(*const f)(uintptr_t err));

void *xres_unwrap_unchecked(XResult res);

XOption xres_get_ok(XResult res);
XOption xres_get_err(XResult res);

#endif
