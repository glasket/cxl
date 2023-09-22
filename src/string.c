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

#include "../include/defs.h"
#include "../include/string.h"
#include <stdlib.h>
#include <string.h>

struct str {
  char8_t *data;
  size_t length;
  size_t capacity;
};

struct strv {
  const char8_t *const str;
  const size_t length;
};

// TODO Replace with Vec once it's implemented

static inline String *string_new_with_capacity_and_length(const size_t capacity, const size_t length) {
  if (length > capacity) {
    return nullptr;
  }
  String *string = malloc(sizeof(String));
  if (string == nullptr) {
    return nullptr;
  }

  if (capacity == 0) {
    string->data = nullptr;
  } else {
    string->data = malloc(capacity * sizeof(char8_t));
    if (string->data == nullptr) {
      free(string);
      return nullptr;
    }
  }

  string->length = length;
  string->capacity = capacity;
  return string;
}

static String *string_new_with_length(const size_t length) {
  return string_new_with_capacity_and_length(length, length);
}

String *string_new() {
  return string_new_with_capacity_and_length(0, 0);
}

String *string_new_with_capacity(const size_t capacity) {
  return string_new_with_capacity_and_length(capacity, 0);
}

String *string_from_bytes(const char8_t *data, const size_t length) {
  String *string = string_new_with_length(length);
  if (string == nullptr) {
    return nullptr;
  }
  memmove(string->data, data, length * sizeof(char8_t));
  string->length = length;
  return string;
}

String *string_from_string_view(const StringView stringView) {
  return string_from_bytes(stringView.str, stringView.length);
}

static StringError string_realloc(String *string, const size_t size) {
  size_t newCap = string->capacity == 0 ? size : string->capacity * 2;
  while (newCap < size) {
    // FIXME: This can infinitely loop, good use for stdckdint.h
    newCap *= 2;
  }
  char8_t *newData = realloc(string->data, newCap * sizeof(char8_t));
  if (newData == nullptr) {
    return STRING_ERR_ALLOC;
  }
  string->data = newData;
  string->capacity = newCap;
}

StringError string_append_byte(String *string, const char8_t other) {
  return string_append_bytes(string, &other, 1);
}

StringError string_append_bytes(String *string, const char8_t *other, const size_t otherLength) {
  if (string->length + otherLength > string->capacity) {
    StringError err = string_realloc(string, string->length + otherLength);
    if (err != STRING_OK) {
      return err;
    }
  }
  memmove(string->data + string->length, other, otherLength * sizeof(char8_t));
  string->length += otherLength;
  return STRING_OK;
}

StringError string_append_string(String *string, const String *other) {
  return string_append_bytes(string, other->data, other->length);
}

StringError string_append_string_view(String *string, const StringView other) {
  return string_append_bytes(string, other.str, other.length);
}