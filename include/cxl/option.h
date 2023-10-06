/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file option.h
 * @brief Option type representing a value that may or may not exist.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#ifndef CXL_OPTION_H
#define CXL_OPTION_H

typedef struct XOption {
  void *data;
  bool is_some;
  bool is_none;
} XOption;

XOption xopt_none(void);
XOption xopt_some(void *const val);

void *xopt_unwrap(XOption opt);
void *xopt_unwrap_or(XOption opt, void *const def);
void *xopt_unwrap_or_else(XOption opt, void *(*const f)(void));

#endif
