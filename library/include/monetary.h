#ifdef CLIB2_STUBS

#ifndef _MONETARY_H
#define _MONETARY_H

/* POSIX.1-2001, POSIX.1-2008. */

#warning "STUB: monetary.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern ssize_t strfmon(char *s, size_t max, const char *format, ...);
extern ssize_t strfmon_l(char *s, size_t max, locale_t locale,
                         const char *format, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#endif /* CLIB2_STUBS */
