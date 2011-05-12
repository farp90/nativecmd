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
#include <ntndk.h>
#include <ntddkbd.h>
#include <debug.h>

#if DBG
#define DEBUG_CHANNEL(ch) static ULONG gDebugChannel = ch;
#else
#define DEBUG_CHANNEL(ch)
#endif

DEBUG_CHANNEL(401);

#define TRACE(fmt, ...)         TRACE__(gDebugChannel, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)          WARN__(gDebugChannel, fmt, ##__VA_ARGS__)
#endif /* __CMD_PRECOMP_H */


#define BUFFER_SIZE 4096

#define CMDLINE_LENGTH  8192

/* 16k = max buffer size */
#define BUFF_SIZE 16384
/* display.c */
VOID DisplayString (char* buffer);
VOID Printf (char* fmt, ...);
VOID Print (char* buffer);
VOID PutChar(WCHAR pChar);

VOID ErrorPrintf (char* fmt, ...);
VOID ErrorPrint (char* buffer);

VOID BufferPrintf (char* fmt, ...);
VOID BufferPrint (char* buffer);
VOID BufferPutChar(WCHAR pChar);
/* input.c */
CHAR GetChar(VOID);
PCHAR ReadLine(VOID);

/* prompt.c */
VOID PrintPrompt(VOID);
