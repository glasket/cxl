/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file error.h
 * @brief Error codes for CXL.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_ERROR_H
#define CXL_ERROR_H

#include <stdint.h>

typedef enum : uintptr_t {
  X_OK,
  X_ERR,
  X_ERR_ALLOC,
  X_ERR_REALLOC,
  X_ERR_DEALLOC,
  X_ERR_BOUNDS,
  X_ERR_OVERFLOW,
  X_ERR_UNDERFLOW,
  X_ERR_EMPTY,
  X_ERR_BAD_ALIGNMENT,
  X_ERR_BAD_LAYOUT,
  X_ERR_BAD_PTR,
  X_ERR_BAD_CAP,
  X_ERR_BAD_PAD,
  X_ERR_BAD_SIZE,
  X_ERR_BAD_INCREASE,
  X_ERR_BAD_SHRINK,
  X_ERR_BAD_OFFSET,
  X_ERR_MISMATCHED_ALIGNMENT
} XErr;

bool xerr_is_ok(XErr err);
bool xerr_is_err(XErr err);

#endif
