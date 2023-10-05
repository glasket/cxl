
#include <assert.h>
#include <cxl/option.h>

XOption xopt_none() {
  return (XOption){.is_some = false, .is_none = true};
}

XOption xopt_some(void *ptr) {
  return (XOption){.is_some = true, .is_none = false, .data = ptr};
}

void *xopt_unwrap(XOption opt) {
  assert(opt.is_some);
  if (opt.is_some) {
    return opt.data;
  }
  return nullptr;
}

void *xopt_unwrap_or(XOption opt, void *def) {
  if (opt.is_some) {
    return opt.data;
  }
  return def;
}

void *xopt_unwrap_or_else(XOption opt, void *(*f)(void)) {
  if (opt.is_some) {
    return opt.data;
  }
  return f();
}