/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file vec.c
 * @brief UTF-8 string types and function declarations.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#include "../include/ckdalloc.h"
#include "../include/defs.h"
#include "../include/vec.h"

struct vec {
  void *data;
  size_t size;
  size_t cap;
};

inline Vec *internal_vec_new(size_t cap, size_t size, void *(*alloc)(size_t num, size_t size)) {
  Vec *vec = alloc(sizeof(Vec));
  if (vec == nullptr) {
    return nullptr;
  }

  if (cap == 0) {
    vec->data = nullptr;
  } else {
    vec->data = alloc(cap, size);
    if (vec->data == nullptr) {
      free(vec);
      return nullptr;
    }
  }

  vec->size = size;
  vec->cap = cap;
  return vec;
}

Vec *vec_new(size_t cap, size_t size) {
  return internal_vec_new(cap, size, ckdalloc);
}

Vec *vec_new_zeroed(size_t cap, size_t size) {
  return internal_vec_new(cap, size, calloc);
}

void vec_free(Vec *vec) {
  if (vec->data != nullptr) {
    free(vec->data);
  }
  free(vec);
}