#ifndef _CRT_PRECOMP_H
#define _CRT_PRECOMP_H

/* We don't want to use the Microsoft CRT inline functions
   so we hack around them in msvc build */
#define _INC_WTIME_INL
#define _INC_UTIME_INL
#define _INC_TIME_INL
#define _CRTIMP
#define _MCRTIMP
#define inline __inline
#define _WIO_DEFINED
/* Headers to be compiled */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <io.h>

#include <sys/stat.h>
#include <sys/locking.h>
#include <share.h>

/* PSDK/NDK Headers */
#define WIN32_NO_STATUS
#include <windows.h>
#include <ndk/ntndk.h>

//#if !defined(_MSC_VER)
//  #include <stdint.h>
//#endif

//#include "wine/unicode.h"
//#include "wine/config.h"

/* kernelmode libcnt should not include Wine-debugging crap */
//#ifndef _LIBCNT_
//#define WINE_NO_TRACE_MSGS
//#include "wine/debug.h"
//#ifndef __WINE_DEBUG_CHANNEL__
//WINE_DEFAULT_DEBUG_CHANNEL(msvcrt);
//#endif
//#else
//#define NDEBUG
#include <debug.h>
//#define TRACE DPRINT
//#define WARN DPRINT1
////#endif
//#if DBG
//#define DEBUG_CHANNEL(ch) static ULONG gDebugChannel = ch;
//#else
//#define DEBUG_CHANNEL(ch)
//#endif
//DEBUG_CHANNEL(301);
//#define TRACE(fmt, ...)         TRACE__(gDebugChannel, fmt, ##__VA_ARGS__)
#define TRACE(fmt, ...)         DPRINT1(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)          DPRINT1(fmt, ##__VA_ARGS__)
#define FIXME(fmt, ...)         DPRINT1(fmt, ##__VA_ARGS__)
#define ERR(fmt, ...)           DPRINT1(fmt, ##__VA_ARGS__)
//#define debugstr_a
//#define debugstr_an
//#define debugstr_w
//#define wine_dbgstr_longlong
//#define TRACE_ON(x) 0
//#define msvcrt
//#undef except
/* CRT Internal data */
//#include <internal/atexit.h>
//#include <internal/console.h>
//#include <internal/file.h>
//#include <internal/ieee.h>
//#include <internal/math.h>
//#include <internal/mbstring.h>
//#include <internal/mtdll.h>
//#include <internal/rterror.h>
//#include <internal/safecrt.h>
//#include <internal/time.h>
//#include <internal/tls.h>
//#include <internal/printf.h>
//typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
//typedef	void (*__p_sig_fn_t)(int);
//#define wine_dbg_sprintf
////#define Spare Flags
//#include "crtfix.h"

#pragma warning(disable:4996)
#endif /* _CRT_PRECOMP_H */
