#include "precomp.h"
BOOLEAN EchoStatus = TRUE;
BOOLEAN ErrorStatus = TRUE;
WCHAR ScreenBuffer[81];
VOID DisplayString (char* buffer)
{
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   RtlInitAnsiString (&AnsiString, buffer);
   RtlAnsiStringToUnicodeString (&UnicodeString,
                 &AnsiString,
                 TRUE);
   NtDisplayString(&UnicodeString);
   RtlFreeUnicodeString (&UnicodeString);
}

VOID Printf (char* fmt, ...)
{
   char buffer[512];
   va_list ap;
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(EchoStatus){
       va_start(ap, fmt);
       vsprintf(buffer, fmt, ap);
       va_end(ap);

       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}

VOID Print (char* buffer)
{
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(EchoStatus){
       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}


VOID PutChar(WCHAR pChar)
{
    WCHAR _PutChar[2] = L" ";
    UNICODE_STRING CharString = {2, 2, _PutChar};
    if(EchoStatus){
        CharString.Buffer[0] = pChar;
        NtDisplayString(&CharString);
    }
}

VOID ErrorPrintf (char* fmt, ...)
{
   char buffer[512];
   va_list ap;
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(ErrorStatus){
       va_start(ap, fmt);
       vsprintf(buffer, fmt, ap);
       va_end(ap);

       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}

VOID ErrorPrint (char* buffer)
{
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(ErrorStatus){
       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}

VOID ScreenBufferCat(WCHAR* pBuffer)
{
    int len1 = wcslen(ScreenBuffer);
    int len2 = wcslen(pBuffer);
    if(len1 + len2 > 80)
    {
        wcscpy(ScreenBuffer, (WCHAR*)&pBuffer[len2 - (len1 + len2) % 80]);
    }
    else
    {
        wcscat(ScreenBuffer, pBuffer);
    }
}

VOID BufferPrintf (char* fmt, ...)
{
   char buffer[512];
   va_list ap;
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(EchoStatus){
       va_start(ap, fmt);
       vsprintf(buffer, fmt, ap);
       va_end(ap);

       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       ScreenBufferCat(UnicodeString.Buffer);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}

VOID BufferPrint (char* buffer)
{
   UNICODE_STRING UnicodeString;
   ANSI_STRING AnsiString;
   if(EchoStatus)
   {
       RtlInitAnsiString (&AnsiString, buffer);
       RtlAnsiStringToUnicodeString (&UnicodeString,
                     &AnsiString,
                     TRUE);
       ScreenBufferCat(UnicodeString.Buffer);
       NtDisplayString(&UnicodeString);
       RtlFreeUnicodeString (&UnicodeString);
   }
}


VOID BufferPutChar(WCHAR pChar)
{
    WCHAR PutChar[2] = L" ";
    UNICODE_STRING CharString = {2, 2, PutChar};
    if(pChar == '\b')
    {
        ScreenBuffer[wcslen(ScreenBuffer)] = '\0';
        CharString.Buffer[0] = '\r';
        NtDisplayString(&CharString);
        RtlInitUnicodeString (&CharString, ScreenBuffer);
        NtDisplayString(&CharString);
    }
    else if(pChar == '\r' || pChar == '\n')
    {
        ScreenBuffer[0] = 0;
    }
    else
    {
        CharString.Buffer[0] = pChar;
        ScreenBufferCat(CharString.Buffer);
        NtDisplayString(&CharString);
    }
}



