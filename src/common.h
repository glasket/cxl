#if !(defined __STDC__ && defined __STDC_VERSION__)
#error "Undetectable C standard version."
#else

#if __STDC_VERSION__ < 202000L
#error "CXL is designed to be used with C23."
#elif __STDC_VERSION__ < 202311L
#warning "CXL is built for use with C23, some features may be missing from C2x compilers."
#include <stddef.h>
#else
#include <stddef.h>
#endif

#endif
