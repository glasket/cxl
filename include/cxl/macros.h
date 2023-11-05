/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file macros.h
 * @brief General header for macros.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#if __STDC_VERSION__ < 2023111L
#define EMPTY_INIT(TYPE) \
  (TYPE) { \
    0 \
  }
#else
#define EMPTY_INIT(TYPE) \
  (TYPE) { \
  }
#endif

#define CAT(x, y) x##y
#define CAT_H(x, y) CAT(x, y)
