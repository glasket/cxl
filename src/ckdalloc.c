/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file ckdalloc.c
 * @brief Wrapper for malloc with calloc API and overflow checks.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "../include/ckdalloc.h"
#include "../include/ckdint.h"
#include "../include/defs.h"

void *ckdalloc(size_t num, size_t size) {
  if (num == 0 || size == 0) {
    return nullptr;
  }

  size_t total = 0;
  if (ckd_mul(&total, num, size)) {
    return nullptr;
  }

  return malloc(total);
}