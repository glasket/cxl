/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file string.h
 * @brief UTF-8 string types and function declarations.
 * @author Christian Sigmon 'Glasket' <cws@glasket.com>
 * @date 2023-
 * @copyright MPL-2.0
 * @version 0.1.0
 */

#pragma once
#include <stdint.h>
#include <uchar.h>

/**
 * @typedef String
 * @brief A UTF-8 string type.
 */
typedef struct str String;

/**
 * @brief Creates and returns an empty string.
 *
 * @return pointer to the new empty string.
 * @retval `NULL` if the string could not be created.
 */
String *string_new();

/**
 * @brief Creates and returns an empty string with the specified capacity.
 *
 * @param[in] capacity the capacity for the new string.
 *
 * @return pointer to the new empty string.
 * @retval `NULL` if the string could not be created.
 */
String *string_new_with_capacity(const size_t capacity);

/**
 * @brief Creates and returns a string from a byte sequence.
 *
 * @param[in] data the `char8_t` sequence to create the string from.
 * @param[in] length the length of the `data` sequence.
 *
 * @return pointer to the new empty string.
 * @retval `NULL` if the string could not be created.
 */
String *string_from_bytes(const char8_t *data, const size_t length);

/**
 * @brief Creates and returns a string from the given StringView.
 *
 * @param[in] stringView the StringView to create the string from.
 *
 * @return pointer to the new empty string.
 * @retval `NULL` if the string could not be created.
 */
String *string_from_string_view(const StringView stringView);

/**
 * @brief Appends a character to the end of the string.
 *
 * @param[in,out] string the string to append to.
 * @param[in] other the character to append.
 */
void string_append_byte(String *string, const char8_t other);

/**
 * @brief Appends a byte sequence to the end of the string.
 *
 * @param[in,out] string the string to append to.
 * @param[in] other the byte sequence to append.
 * @param[in] otherLength the length of the character array.
 */
void string_append_bytes(String *string, const char8_t *other,
                         int otherLength);

/**
 * @brief Appends a String to the end of the string.
 *
 * @param[in,out] string the string to append to.
 * @param[in] other the String to append.
 */
void string_append_string(String *string, const String *other);

/**
 * @brief Appends a StringView to the end of the string.
 * @param[in,out] string the string to append to.
 * @param[in] other the StringView to append.
 */
void string_append_string_view(String *string, const StringView *other);

/**
 * @brief Slices and returns a view of the string from `start` to `end`.
 *
 * @param[in] string the string to slice.
 * @param[in] start the start index of the slice.
 * @param[in] end the end index of the slice.
 *
 * @return a view of the string from `start` to `end`.
 * @retval `NULL` if the slice could not be created.
 */
StringView string_slice(const String *string, const size_t start, const size_t end);

/**
 * @brief Returns the length of the string.
 *
 * @param[in] string the string to get the length of.
 *
 * @return the length of the string.
 * @retval `0` if the string is `NULL`.
 */
size_t string_len(String *string);

/**
 * @brief Returns the capacity of the string.
 *
 * @param[in] string the string to get the capacity of.
 *
 * @return the capacity of the string.
 * @retval `0` if the string is `NULL`.
 */
size_t string_cap(String *string);

/**
 * @brief Empties the string.
 *
 * @param[in,out] string the string to clear.
 *
 * @note This does not reduce the capacity of the string.
 */
void string_clear(String *string);

/**
 * @brief Returns `true` if the string's length is `0`.
 *
 * @param[in] string the string to check.
 *
 * @return if the string is empty.
 * @retval `true` if string length is `0`.
 * @retval `false` if string length is not `0`.
 */
bool string_is_empty(const String *string);

/**
 * @brief Reserves capacity for the string.
 *
 * @param[in,out] string the string to reserve capacity for.
 * @param[in] additional the extra capacity to reserve.
 */
void string_reserve(String *string, const size_t additional);

/**
 * @brief Frees the string's memory.
 *
 * @param[in,out] string the string to free.
 */
void string_free(String *string);

/**
 * @typedef StringView
 * @brief Provides a fixed-width view over an underlying @ref String.
 *
 * @warning If the underlying @ref String mutates then accessing the StringView
 * may result in undefined behavior.
 *
 * @remark This is effectively a fat pointer a la Rust's `&str`.
 */
typedef struct strv StringView;

/**
 * @brief Creates and returns a StringView of the given byte sequence.
 *
 * @param[in] data the byte sequence to create the StringView on.
 *
 * @return a StringView of the given byte sequence.
 * @retval `NULL` if the StringView could not be created.
 */
StringView string_view_from_bytes(const char8_t *data, const size_t length);

/**
 * @brief Creates and returns a StringView of the given String.
 *
 * @param[in] string the string to create the StringView on.
 *
 * @return a StringView of the given String.
 * @retval `NULL` if the StringView could not be created.
 */
StringView string_view_from_string(const String *string);

/**
 * @brief Creates and StringView by slicing another StringView.
 *
 * @param[in] stringView the StringView to slice.
 * @param[in] start the start index of the slice.
 * @param[in] end the end index of the slice.
 *
 * @return a new StringView that's a slice of the given StringView.
 * @retval `NULL` if the StringView could not be created.
 */
StringView string_view_slice(const StringView stringView, const size_t start,
                             const size_t end);
