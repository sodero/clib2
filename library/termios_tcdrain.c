/*
 * $Id: termios_tcdrain.c,v 1.2 2005-07-06 18:48:53 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2005 by Olaf Barthel <olsen@sourcery.han.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_TERMIOS_HEADERS_H
#include "termios_headers.h"
#endif /* _TERMIOS_HEADERS_H */

/****************************************************************************/

#if defined(__amigaos4__) && !defined(Flush)
#define Flush(fh) FFlush(fh)
#endif /* __amigaos4__ && !Flush */

/****************************************************************************/

int
tcdrain(int file_descriptor) 
{
	int result = ERROR;
	struct fd *fd;
	struct termios *tios;
	BPTR file;

	ENTER();

	SHOWVALUE(file_descriptor);

	if(__check_abort_enabled)
		__check_abort();

	__stdio_lock();

	fd = __get_file_descriptor(file_descriptor);
	if(fd == NULL)
	{
		__set_errno(EBADF);
		goto out;
	}

	__fd_lock(fd);

	file = fd->fd_DefaultFile;

	#if defined(__THREAD_SAFE)
	{
		if(FLAG_IS_SET(fd->fd_Flags,FDF_STDIO))
		{
			switch(fd->fd_DefaultFile)
			{
				case STDIN_FILENO:

					file = Input();
					break;

				case STDOUT_FILENO:

					file = Output();
					break;

				case STDERR_FILENO:

					#if defined(__amigaos4__)
					{
						file = ErrorOutput();
					}
					#else
					{
						struct Process * this_process = (struct Process *)FindTask(NULL);

						file = this_process->pr_CES;
					}
					#endif /* __amigaos4__ */

					/* The following is rather controversial; if the standard error stream
					   is unavailable, we default to reuse the standard output stream. This
					   is problematic if the standard output stream was redirected and should
					   not be the same as the standard error output stream. */
					if(file == ZERO)
						file = Output();

					break;

				default:

					file = ZERO;
					break;
			}
		}
	}
	#endif /* __THREAD_SAFE */

	if(FLAG_IS_SET(fd->fd_Flags,FDF_TERMIOS))
	{
		tios = fd->fd_Aux;

		switch(tios->type)
		{
			case TIOST_CONSOLE:

				if(file == ZERO)
				{
					__set_errno(EBADF);
					goto out;
				}

				/* This also discards any buffered input, but it does
				   not appear possible to drain the output buffer
				   otherwise. (?) */
				if(CANNOT Flush(file))
					goto out;

				break;

			default: /* TODO: Serial port support. */

				__set_errno(ENXIO);
				goto out;
		}

		result = OK;
	}
	else
	{
		result = fdatasync(file_descriptor); /* If called on a "regular" file. */
	}

 out:

	__fd_unlock(fd);

	__stdio_unlock();

	RETURN(result);
	return(result);
}