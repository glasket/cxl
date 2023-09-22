/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file defs.h
 * @brief Shim defs for incomplete C23 features.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#if (defined(__STDC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202311L))
#include <stddef.h> /* nullptr_t */
#else
#define nullptr (void *)0
typedef void *nullptr_t;
#endif
