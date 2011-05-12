/*
 * PROJECT:         ReactOS Session Manager
 * LICENSE:         GPL v2 or later - See COPYING in the top level directory
 * FILE:            base/system/smss/print.c
 * PURPOSE:         Print on the blue screen.
 * PROGRAMMERS:     ReactOS Development Team
 */

/* INCLUDES ******************************************************************/

#include <precomp.h>

VOID DisplayString(LPCWSTR lpwString)
{
   UNICODE_STRING us;

   RtlInitUnicodeString (&us, lpwString);
   NtDisplayString (&us);
}

VOID PrintString (char* fmt, ...)
{
   char buffer[512];
   va_list ap;
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;

   va_start(ap, fmt);
   vsprintf(buffer, fmt, ap);
   va_end(ap);
   DPRINT1("%s\n", buffer);

   RtlInitAnsiString (&AnsiString, buffer);
   RtlAnsiStringToUnicodeString (&UnicodeString,
				 &AnsiString,
				 TRUE);
   NtDisplayString(&UnicodeString);
   RtlFreeUnicodeString (&UnicodeString);
}

VOID PutChar(WCHAR Char)
{
    WCHAR PutChar[2] = L" ";
    UNICODE_STRING CharString = {2, 2, PutChar};
    CharString.Buffer[0] = Char;
    NtDisplayString(&CharString);
}
/* EOF */
