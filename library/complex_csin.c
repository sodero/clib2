/*
 * Experimental: Not a part of clib2 from Olaf Barthel
 */

#ifndef _COMPLEX_HEADERS_H
#include "complex_headers.h"
#endif /* _COMPLEX_HEADERS_H */

/****************************************************************************/

#if defined(COMPLEX_SUPPORT)

/****************************************************************************/

double complex
csin(double complex z)
{
    z = csinh(CMPLX(-cimag(z), creal(z)));
    return CMPLX(cimag(z), -creal(z));
}

/****************************************************************************/

#endif /* COMPLEX_SUPPORT */