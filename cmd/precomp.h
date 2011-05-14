#ifndef __CMD_PRECOMP_H
#define __CMD_PRECOMP_H

#ifdef _MSC_VER
#pragma warning ( disable : 4103 ) /* use #pragma pack to change alignment */
#undef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif//_MSC_VER

#include <stdlib.h>
#include <malloc.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <winnt.h>
#include <shellapi.h>

#include <tchar.h>
#include <direct.h>

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define NTOS_MODE_USER
#include <ndk/ntndk.h>
//#include <bootvid.h>
#include "resource.h"

#include "cmd.h"
#include "config.h"
#include "batch.h"

#include <reactos/buildno.h>
#include <reactos/version.h>

#include <debug.h>
//WINE_DEFAULT_DEBUG_CHANNEL(cmd);
//#ifdef UNICODE
//#define debugstr_aw debugstr_w
//#else
//#define debugstr_aw debugstr_a
//#endif
#if DBG
#define DEBUG_CHANNEL(ch) static ULONG gDebugChannel = ch;
#else
#define DEBUG_CHANNEL(ch)
#endif
DEBUG_CHANNEL(201);
#define TRACE(fmt, ...)         TRACE__(gDebugChannel, fmt, ##__VA_ARGS__)
//#define TRACE(fmt, ...)         DPRINT1(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)          WARN__(gDebugChannel, fmt, ##__VA_ARGS__)
#define _ANONYMOUS_UNION
#pragma warning(disable:4716)

VOID DisplayString(LPCWSTR lpwString);
VOID PrintString (char* fmt, ...);
VOID PutChar(WCHAR Char);
#ifndef CreateSymbolicLink
WINBASEAPI
BOOLEAN
APIENTRY
CreateSymbolicLinkA (
    __in LPCSTR lpSymlinkFileName,
    __in LPCSTR lpTargetFileName,
    __in DWORD dwFlags
    );
WINBASEAPI
BOOLEAN
APIENTRY
CreateSymbolicLinkW (
    __in LPCWSTR lpSymlinkFileName,
    __in LPCWSTR lpTargetFileName,
    __in DWORD dwFlags
    );
#ifdef _UNICODE
#define CreateSymbolicLink  CreateSymbolicLinkW
#else
#define CreateSymbolicLink  CreateSymbolicLinkA
#endif // !UNICODE
#endif
#endif /* __CMD_PRECOMP_H */
