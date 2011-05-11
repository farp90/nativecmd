/*++

Copyright (c) Alex Ionescu.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED UNDER THE LESSER GNU PUBLIC LICENSE.
    PLEASE READ THE FILE "COPYING" IN THE TOP LEVEL DIRECTORY.

Module Name:

    precomp.h

Abstract:

    The Native Command Line Interface (NCLI) is the command shell for the
    TinyKRNL OS.

Environment:

    Native mode

Revision History:

    Alex Ionescu - Started Implementation - 23-Mar-06

--*/
#define WIN32_NO_STATUS
#define NTOS_MODE_USER
#include <stdio.h>
#include <stdarg.h>
#include <excpt.h>
#include <windows.h>
#include <windef.h>
#include <winnt.h>
#include <ntndk.h>
#include <ntddkbd.h>

/* display.c */
BOOLEAN ECHO_STATUS = 1;
BOOLEAN ERROR_STATUS = 1;

VOID DisplayString (char* buffer);
VOID Printf (char* fmt, ...);
VOID Print (char* buffer);
VOID PutChar(WCHAR pChar);

VOID ErrorPrintf (char* fmt, ...);
VOID ErrorPrint (char* buffer);

VOID BufferPrintf (char* fmt, ...);
VOID BufferPrint (char* buffer);
VOID BufferPutChar(WCHAR pChar);
/*/ display.c */


typedef struct _COMMAND
{
	LPTSTR name;
	INT    flags;
	INT    (*func)(LPTSTR);
} COMMAND, *LPCOMMAND;