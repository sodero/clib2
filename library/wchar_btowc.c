/*
 * FIXME: From MUSL.
 */

#ifndef _WCHAR_HEADERS_H
#include "wchar_headers.h"
#endif /* _WCHAR_HEADERS_H */

/****************************************************************************/

wint_t
btowc(int c)
{
    int b = (unsigned char) c;
    return b < 128U ? b : (MB_CUR_MAX == 1 && c != EOF) ? CODEUNIT(c) : WEOF;
}
