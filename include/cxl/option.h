
#pragma once
#ifndef CXL_OPTION_H
#define CXL_OPTION_H

typedef struct XOption {
  void *data;
  bool is_some;
  bool is_none;
} XOption;

XOption xopt_none(void);
XOption xopt_some(void *const val);

void *xopt_unwrap(XOption opt);
void *xopt_unwrap_or(XOption opt, void *const def);
void *xopt_unwrap_or_else(XOption opt, void *(*const f)(void));

#endif
