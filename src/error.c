#include <cxl/error.h>

bool xerr_is_ok(XErr err) {
  return err == X_OK;
}
bool xerr_is_err(XErr err) {
  return err != X_OK;
}
