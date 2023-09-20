/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file string.c
 * @brief UTF-8 string types and function definitions
 * @author Christian Sigmon 'Glasket'
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "../include/string.h"

struct str
{
    char8_t *data;
    size_t length;
    size_t capacity;
};

struct strv
{
    const char8_t *const str;
    const size_t length;
};
