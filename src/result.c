#include <assert.h>
#include <cxl/result.h>

XResult xres_ok(void *ptr) {
  return (XResult){.res.ptr = ptr, .is_err = false, .is_ok = true};
}

XResult xres_err(uintptr_t err) {
  return (XResult){.res.err = err, .is_err = true, .is_ok = false};
}

void *xres_unwrap(XResult res) {
  assert(res.is_ok);
  if (res.is_ok) {
    return res.res.ptr;
  }
  return nullptr;
}

void *xres_unwrap_or(XResult res, void *def) {
  if (res.is_ok) {
    return res.res.ptr;
  }
  return def;
}

void *xres_unwrap_or_else(XResult res, void *(*or_else)(uintptr_t err)) {
  if (res.is_ok) {
    return res.res.ptr;
  }
  return or_else(res.res.err);
}

void *xres_unwrap_unchecked(XResult res) {
  return res.res.ptr;
}

XOption xres_get_ok(XResult res) {
  if (res.is_ok) {
    return xopt_some(res.res.ptr);
  }
  return xopt_none();
}

XOption xres_get_err(XResult res) {
  if (res.is_err) {
    return xopt_some((void *)res.res.err);
  }
  return xopt_none();
}