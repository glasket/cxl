
#include <stddef.h>

typedef enum mem_err {
  MEM_OK = 0,
  MEM_ERR_ALLOC,
  MEM_ERR_OVERFLOW,
  MEM_ERR_INVALID_SET,
  MEM_ERR_INVALID_SHRINK,
} MemErr;

typedef struct Layout {
  size_t size;
  size_t alignment;
} Layout;

/**
 * @brief Allocates a new buffer with the specified layout.
 *
 * @param[in] layout The layout of the buffer to allocate.
 *
 * @return Pointer to the allocated buffer.
 * @retval nullptr if allocation failed.
 */
typedef void *(*cxl_mem_allocate)(const Layout layout, const size_t pad);

/**
 * @brief Reallocates a buffer with the specified layout.
 *
 * @param[in] ptr Pointer to the buffer to reallocate.
 * @param[in] old_layout The layout of the buffer before reallocation. Useful if zeroing.
 * @param[in] new_layout The layout of the buffer after reallocation.
 *
 * @return Pointer to the reallocated buffer.
 * @retval nullptr if reallocation failed.
 */
typedef void *(*cxl_mem_reallocate)(
    void *const ptr, const Layout old_layout, const Layout new_layout, const size_t pad
);

/**
 * @brief Deallocates a buffer.
 *
 * @param[in] buf Pointer to the buffer to deallocate.
 * @param[in] full_size The full size of the buffer. For zeroing.
 */
typedef void (*cxl_mem_deallocate)(void *const buf, const size_t full_size);

typedef struct Allocator {
  cxl_mem_allocate alloc;
  cxl_mem_reallocate realloc;
  cxl_mem_deallocate free;
} Allocator;

void *balloc(const Layout layout, const size_t pad);
void *zballoc(const Layout layout, const size_t pad);

void *brealloc(void *const ptr, const Layout old_layout, const Layout new_layout, const size_t pad);
void *zbrealloc(void *const ptr, const Layout old_layout, const Layout new_layout, const size_t pad);

void bfree(void *const ptr, const size_t full_size);
void zbfree(void *const ptr, const size_t full_size);

const Allocator GlobalAllocator = {
    .alloc = balloc,
    .realloc = brealloc,
    .free = bfree,
};

// Also does overflow checks
const Allocator ZeroAllocator = {
    .alloc = zballoc,
    .realloc = zbrealloc,
    .free = zbfree,
};
