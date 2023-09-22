/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file ckdalloc.h
 * @brief Wrapper for malloc with calloc API and overflow checks.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#include <stdlib.h>

/**
 * @brief Wrapper for malloc with calloc API and overflow checks.
 *
 * @param[in] num Number of elements to allocate.
 * @param[in] size Size of each chunk to allocate.
 *
 * @return Pointer to allocated memory.
 * @retval nullptr if memory allocation failed or if overflow occurred.
 */
void *ckdalloc(size_t num, size_t size);