
#include "ckdint.h"
#include <cxl/mem/alloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static size_t layout_size(const Layout layout, const size_t pad) {
  if (layout.size == 0 || layout.alignment == 0) {
    return 0;
  }

  size_t total = 0;
  if (ckd_mul(&total, layout.size, layout.alignment) || ckd_add(&total, total, pad)) {
    return 0;
  }

  return total;
}

static bool layout_eq(const Layout a, const Layout b) {
  return a.size == b.size && a.alignment == b.alignment;
}

void *balloc(const Layout layout, const size_t pad) {
  size_t total = layout_size(layout, pad);
  if (total == 0) {
    return nullptr;
  }
  return malloc(total);
}

void *zballoc(const Layout layout, const size_t pad) {
  size_t total = layout_size(layout, pad);
  if (total == 0) {
    return nullptr;
  }
  return calloc(1, total);
}

void *brealloc(void *const ptr, const Layout old_layout, const Layout new_layout, const size_t pad) {
  size_t total = layout_size(new_layout, pad);
  if (total == 0) {
    return nullptr;
  }
  return realloc(ptr, total);
}

void *zbrealloc(void *const ptr, const Layout old_layout, const Layout new_layout, const size_t pad) {
  if (layout_eq(old_layout, new_layout)) {
    return ptr;
  }

  size_t total = layout_size(new_layout, pad);
  if (total == 0) {
    return nullptr;
  }

  // Old size can't overflow.
  size_t old_size = old_layout.size * old_layout.alignment + pad;

  if (total < old_size) {
    memset((uint8_t *)total, 0, old_size - total);
    return realloc(ptr, total);
  }
  void *tmp = realloc(ptr, total);
  memset((uint8_t *)tmp + old_size, 0, total - old_size);
  return tmp;
}

void bfree(void *const ptr, const size_t full_size) {
  free(ptr);
}

void zbfree(void *const ptr, const size_t full_size) {
  memset(ptr, 0, full_size);
  free(ptr);
}