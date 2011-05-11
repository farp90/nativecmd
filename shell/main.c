/*++

Copyright (c) Alex Ionescu.  All rights reserved.
Copyright (c) 2011 amdf.

    THIS CODE AND INFORMATION IS PROVIDED UNDER THE LESSER GNU PUBLIC LICENSE.
    PLEASE READ THE FILE "COPYING" IN THE TOP LEVEL DIRECTORY.

Module Name:

    main.c

Abstract:

    The Native Command Line Interface (NCLI) is the command shell for the
    TinyKRNL OS.
    This module handles the main command line interface and command parsing.

Environment:

    Native mode

Revision History:

    Alex Ionescu - Started Implementation - 01-Mar-06
    Alex Ionescu - Reworked architecture - 23-Mar-06
    amdf         - Added process launch command - 25-Jan-11
    amdf         - Added move command - 20-Feb-11

--*/
#include "precomp.h"
#include "mspack.h"
#include "laotou.h"
HANDLE hKeyboard;
HANDLE hHeap;
HANDLE hKey;

#define __NCLI_VER__ "0.12 x86"
WCHAR *helpstr[] =
{
    {
        L"\n"
        L"cd X     - Change directory to X    md X     - Make directory X\n"
        L"copy X Y - Copy file X to Y         poweroff - Power off PC\n"
        L"dir      - Show directory contents  pwd      - Print working directory\n"
        L"del X    - Delete file X            reboot   - Reboot PC\n"
        L"devtree  - Dump device tree         shutdown - Shutdown PC\n"
        L"\x0000"
    },
    {
        L"exit     - Exit shell               sysinfo  - Dump system information\n"
        L"lm       - List modules             vid      - Test screen output\n"
        L"lp       - List processes           move X Y - Move file X to Y\n"
        L"if       - Condition                load X   - Load a batch file\n"
        L"expand   - expand a .cab file\n"
        L"\n"
        L"If a command is not in the list, it is treated as an executable name\n"
        L"\n"
        L"\x0000"
    }
};
/*++
 * @name RtlClipProcessMessage
 *
 * The RtlClipProcessMessage routine
 *
 * @param Command
 *        FILLMEIN
 *
 * @return None.
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/
VOID
RtlClipProcessMessage(PCHAR Command)
{
    WCHAR CurrentDirectory[MAX_PATH];
    WCHAR buf1[MAX_PATH];
    WCHAR buf2[MAX_PATH];
    UNICODE_STRING CurrentDirectoryString;
    CHAR CommandBuf[BUFFER_SIZE];
    //
    // Copy command line and break it to arguments
    //
    // if xargc = 3, then xargv[1], xargv[2], xargv[3] are available
    // xargv[1] is a command name, xargv[2] is the first parameter

    memset(CommandBuf, 0x00, BUFFER_SIZE);
    strncpy(CommandBuf, Command, strnlen(Command, BUFFER_SIZE));
    StringToArguments(CommandBuf);
    xargc--;//xargc is big than the length of xargv
    //
    // We'll call the handler for each command
    //
    if (!_stricmp(xargv[1], "exit"))
    {
        //
        // Exit from shell
        //
        DeinitHeapMemory( hHeap );
        NtTerminateProcess(NtCurrentProcess(), 0);
    }
    else if (!_stricmp(xargv[1], "test"))
    {
        UINT i = 0;

        RtlCliDisplayString("Args: %d\n", xargc);
        for (i = 1; i < xargc; i++)
        {
            RtlCliDisplayString("Arg %d: %s\n", i, xargv[i]);
        }
    }
    else if (!_stricmp(xargv[1], "help"))
    {
        RtlCliDisplayString("%S", helpstr[0]);
        RtlCliDisplayString("%S", helpstr[1]);
    }
    else if (!_stricmp(xargv[1], "lm"))
    {
        //
        // List Modules (!lm)
        //
        RtlCliListDrivers();
    }
    else if (!_stricmp(xargv[1], "lp"))
    {
        //
        // List Processes (!lp)
        //
        RtlCliListProcesses();
    }
    else if (!_stricmp(xargv[1], "sysinfo"))
    {
        //
        // Dump System Information (sysinfo)
        //
        RtlCliDumpSysInfo();
    }
    else if (!_stricmp(xargv[1], "cd"))
    {
        //
        // Set the current directory
        //
        RtlCliSetCurrentDirectory(xargv[2]);
    }
    //else if (!_stricmp(xargv[1], "locale"))
    //{
    ////
    //// Set the current directory
    ////

    //NtSetDefaultLocale(TRUE, 1049);
    //}
    else if (!_stricmp(xargv[1], "pwd"))
    {
        //
        // Get the current directory
        //
        RtlCliGetCurrentDirectory(CurrentDirectory);

        //
        // Display it
        //
        RtlInitUnicodeString(&CurrentDirectoryString, CurrentDirectory);
        RtlCliPrintString(&CurrentDirectoryString);

        RtlFreeUnicodeString(&CurrentDirectoryString);
    }
    else if (!_stricmp(xargv[1], "dir"))
    {
        //
        // List the current directory
        //
        RtlCliListDirectory();
    }
    else if (!_stricmp(xargv[1], "devtree"))
    {
        //
        // Dump hardware tree
        //
        RtlCliListHardwareTree();
    }
    else if (!_stricmp(xargv[1], "shutdown"))
    {
        RtlCliShutdown();
    }
    else if (!_stricmp(xargv[1], "reboot"))
    {
        RtlCliReboot();
    }
    else if (!_stricmp(xargv[1], "poweroff"))
    {
        RtlCliPowerOff();
    }
    else if (!_stricmp(xargv[1], "vid"))
    {
        UINT j;
        WCHAR i, w;
        UNICODE_STRING us;

        LARGE_INTEGER delay;
        memset(&delay, 0x00, sizeof(LARGE_INTEGER));
        delay.LowPart = 100000000;


        RtlInitUnicodeString(&us, L" ");

        //75x23
        RtlCliDisplayString("\nVid mode is 75x23\n\nCharacter test:");

        j = 0;
        for (w = L'A'; w < 0xFFFF; w++)
        {
            j++;
            NtDelayExecution(FALSE, &delay);
            //w = i;
            if (w != L'\n' && w != L'\r')
            {
                RtlCliPutChar(w);
            }
            else
            {
                RtlCliPutChar(L' ');
            }
            if (j > 70)
            {
                j = 0;
                RtlCliPutChar(L'\n');
            }
        }
    }
    else if (!_stricmp(xargv[1], "copy"))
    {
        // Copy file
        if (xargc > 2)
        {
            GetFullPath(xargv[2], buf1, FALSE);
            GetFullPath(xargv[3], buf2, FALSE);
            RtlCliDisplayString("\nCopy %S to %S\n", buf1, buf2);
            if (FileExists(buf1))
            {
                if (!NtFileCopyFile(buf1, buf2))
                {
                    RtlCliDisplayString("Failed.\n");
                }
            }
            else
            {
                RtlCliDisplayString("File does not exist.\n");
            }
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else if (!_stricmp(xargv[1], "move"))
    {
        // Move/rename file
        if (xargc > 2)
        {
            GetFullPath(xargv[2], buf1, FALSE);
            GetFullPath(xargv[3], buf2, FALSE);
            RtlCliDisplayString("\nMove %S to %S\n", buf1, buf2);
            if (FileExists(buf1))
            {
                if (!NtFileMoveFile(buf1, buf2, FALSE))
                {
                    RtlCliDisplayString("Failed.\n");
                }
            }
            else
            {
                RtlCliDisplayString("File does not exist.\n");
            }
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else if (!_stricmp(xargv[1], "del"))
    {
        // Delete file
        if (xargc > 1)
        {
            GetFullPath(xargv[2], buf1, FALSE);
            if (FileExists(buf1))
            {
                RtlCliDisplayString("\nDelete %S\n", buf1);

                if (!NtFileDeleteFile(buf1))
                {
                    RtlCliDisplayString("Failed.\n");
                }
            }
            else
            {
                RtlCliDisplayString("File does not exist.\n");
            }
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else if (!_stricmp(xargv[1], "md"))
    {
        // Make directory
        if (xargc > 1)
        {
            GetFullPath(xargv[2], buf1, FALSE);

            RtlCliDisplayString("\nCreate directory %S\n", buf1);

            if (!NtFileCreateDirectory(buf1))
            {
                RtlCliDisplayString("Failed.\n");
            }
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else if (!_stricmp(xargv[1], "expand"))
    {
        // Expand .cab file
        void CabinetExpand(char * cabname, char * target);
        if(!_stricmp(xargv[2], "-d") && xargc > 2)
        {
            CabinetExpand(xargv[3], NULL);
        }
        else if(xargc > 1)
        {
            CabinetExpand(xargv[2], xargv[3]);
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else if (!_stricmp(xargv[1], "if"))
    {
        void IfCondition( PCHAR Command);
        IfCondition(Command);
    }
    else if (!_stricmp(xargv[1], "load"))
    {
        void LoadBatch(PCHAR Command, WCHAR * fname);
        GetFullPath(xargv[2], buf1, FALSE);
        LoadBatch(Command, buf1);
    }
    else if (!_stricmp(xargv[1], "mount"))
    {
        DWORD wIndex;
        if(xargc >=3){
            GetFullPath(xargv[2], buf2, FALSE);
            if (xargc == 3)
            {
                GetFullPath(xargv[3], buf1, FALSE);
                wIndex = 1;
            }
            else
            {
                GetFullPath(xargv[4], buf1, FALSE);
                wIndex = strtoul(xargv[3], NULL, 10);
            }
            wIndex = LaotouMountImage(buf1, buf2, wIndex, NULL);
            if(!wIndex)
            {
                 RtlCliDisplayString("Mount Success.\n");
            }
            else
            {
                 RtlCliDisplayString("Mount Failed 0x%.8X.\n", wIndex);
            }
        }
        else
        {
            RtlCliDisplayString("Not enough arguments.\n");
        }
    }
    else
    {
        //
        // Unknown command, try to find an executable and run it.
        // Executable name should be with an .exe extension.
        //
        WCHAR filename[MAX_PATH];
        ANSI_STRING as;
        UNICODE_STRING us;
        HANDLE hProcess;

        GetFullPath(IN xargv[1], OUT filename, FALSE);

        if (FileExists(filename))
        {
            RtlInitAnsiString(&as, Command);
            RtlAnsiStringToUnicodeString(&us, &as, TRUE);

            NtClose(hKeyboard);
            //RtlCliDisplayString("Keyboard is closed\n");

            CreateNativeProcess(filename, us.Buffer, &hProcess);

            RtlFreeAnsiString(&as);
            RtlFreeUnicodeString(&us);

            //RtlCliDisplayString("Waiting for process terminations\n");
            NtWaitForSingleObject(hProcess, FALSE, NULL);

            RtlCliOpenInputDevice(&hKeyboard, KeyboardType);
            //RtlCliDisplayString("Keyboard restored\n");
        }
        else
        {
            RtlCliDisplayString("unkonwn command : %s\n", Command);
        }
    }
}

/*++
 * @name RtlClipDisplayPrompt
 *
 * The RtlClipDisplayPrompt routine
 *
 * @param None.
 *
 * @return None.
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/
VOID
RtlClipDisplayPrompt(VOID)
{
    WCHAR CurrentDirectory[MAX_PATH];
    ULONG DirSize;
    UNICODE_STRING DirString;

    //
    // Get the current directory
    //
    DirSize = RtlCliGetCurrentDirectory(CurrentDirectory) / sizeof(WCHAR);

    //
    // Display it
    //
    CurrentDirectory[DirSize] = L'>';
    CurrentDirectory[DirSize + 1] = UNICODE_NULL;
    RtlInitUnicodeString(&DirString, CurrentDirectory);
    RtlCliPrintString(&DirString);
}

/*++
 * @name main
 *
 * The main routine
 *
 * @param argc
 *        FILLMEIN
 *
 * @param argv[]
 *        FILLMEIN
 *
 * @param envp[]
 *        FILLMEIN
 *
 * @param DebugFlag
 *        FILLMEIN
 *
 * @return NTSTATUS
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/
NTSTATUS
__cdecl
main(INT argc,
     PCHAR argv[],
     PCHAR envp[],
     ULONG DebugFlag OPTIONAL)
{
    PPEB Peb = NtCurrentPeb();
    NTSTATUS Status;
    PCHAR Command;
    char buf[BUFFER_SIZE];
    int i;
    hHeap = InitHeapMemory();
    hKey = NULL;
    //
    // Show banner
    //
    RtlCliDisplayString("Native Shell [Version " __NCLI_VER__ "] (" __DATE__ " " __TIME__ ")\n");
    RtlCliDisplayString("(C) Copyright 2010-2011 amdf\n");
    RtlCliDisplayString("(C) Copyright 2006 TinyKRNL Project\n\n");
    RtlCliDisplayString("Type \"help\".\n\n");
    DbgPrint("************Native Shell START************\n");
    // Setup keyboard input
    //
    if(argc > 1)
    {
        Command = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, BUFFER_SIZE);
        for(i = 1; i < argc; i++)
        {
            strcat(Command, argv[i]);
            strcat(Command, " ");
        }
        RtlClipProcessMessage(Command);
        RtlFreeHeap(RtlGetProcessHeap(), 0, Command);
        //DeinitHeapMemory( hHeap );
        //NtTerminateProcess(NtCurrentProcess(), 0);
    }
    Status = RtlCliOpenInputDevice(&hKeyboard, KeyboardType);

    //
    // Show initial prompt
    //
    RtlClipDisplayPrompt();
    //
    // Wait for a new line
    //
    while (TRUE)
    {
        //
        // Get the line that was entered and display a new line
        //
        Command = RtlCliGetLine(hKeyboard);
        RtlCliDisplayString("\n");

        //
        // Make sure there's actually a command
        //
        if (*Command)
        {
            //
            // Process the command and do a new line again.
            //
            RtlClipProcessMessage(Command);
            RtlCliDisplayString("\n");
        }

        //
        // Display the prompt, and restart the loop
        //
        RtlClipDisplayPrompt();
        continue;
    }
    DbgPrint("************Native Shell End************\n");
    DeinitHeapMemory( hHeap );
    NtTerminateProcess( NtCurrentProcess(), 0 );

    //
    // Return
    //
    return STATUS_SUCCESS;
}
void IfCondition(PCHAR Command)
{
    unsigned int i = 2;
    WCHAR buf[MAX_PATH];
    if(!_stricmp(xargv[2], "not"))
    {
        i++;
    }
    if(!_stricmp(xargv[i], "exist"))
    {
        GetFullPath(xargv[++i], buf, FALSE);
        if(!_stricmp(xargv[2], "not") ^ (FileExists(buf) || FolderExists(buf)))
        {
            strcpy(Command, xargv[++i]);
            for(i++; i <= xargc; i++)
            {
                strcat(Command, " ");
                strcat(Command, xargv[i]);
            }
            RtlClipProcessMessage(Command);
        }
    }
}
void LoadBatch(PCHAR Command, WCHAR *fname)
{
    HANDLE hFile;
    IO_STATUS_BLOCK sIoStatus;
    NTSTATUS ntStatus;
    char *buf;
    off_t offset = 0;
    DWORD i, pos = 0;
    if(!NtFileOpenFile( &hFile , fname, FALSE, FALSE))
    {
        RtlCliDisplayString("file open error.\n");
        return;
    }
    buf = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH);
    while(pos < BUFFER_SIZE)
    {
        ntStatus = 0;
        memset(&sIoStatus, 0, sizeof(IO_STATUS_BLOCK));
        NtFileSeekFile(hFile, offset);
        ntStatus = NtReadFile( hFile, NULL, NULL, NULL, &sIoStatus, buf, MAX_PATH, NULL, NULL);
        for(i = 0; i < sIoStatus.Information || ntStatus == STATUS_END_OF_FILE; i++)
        {
            if(pos >= BUFFER_SIZE - 1)
            {
                RtlCliDisplayString("Command buffer overflow.\n");
                break;
            }
            offset++;
            if(buf[i] == '\r' || buf[i] == '\n' || ntStatus == STATUS_END_OF_FILE)
            {
                if(pos)
                {
                    Command[pos] = '\0';
                    pos = 0;
                    RtlClipDisplayPrompt();
                    RtlCliDisplayString("%s\n", Command);
                    RtlClipProcessMessage(Command);
                }
                break;
            }
            Command[pos++] = buf[i];
        }
        if (ntStatus == STATUS_END_OF_FILE)
        {
            break;
        }
        else if (ntStatus != STATUS_SUCCESS)
        {
            RtlCliDisplayString("file read error.\n");
            break;
        }
    }
    RtlFreeHeap(RtlGetProcessHeap(), 0, buf);
    NtClose(hFile);
}
void CabinetExpand(char *cabname, char *target)
{

    struct mscab_decompressor *cabd;
    struct mscabd_cabinet *cab;
    struct mscabd_file *file;
    char buf[MAX_PATH];
    char *p;
    int count_ok = 0, count_err = 0, count = 0;
    int err;
#if 1
    __asm
    {
        int 3;
    }
#endif
    MSPACK_SYS_SELFTEST(err);
    if (err)
    {
        RtlCliDisplayString("selftest error : %d.\n", err);
        return ;
    }
    if (!(cabd = mspack_create_cab_decompressor(NULL)))
    {
        RtlCliDisplayString("can't make decompressor\n");
        return ;
    }
    if(!(cab = cabd->open(cabd, cabname)))
    {
        RtlCliDisplayString("can't open file. error : %d.\n", cabd->last_error(cabd));
    }
    else
    {
        if (!_stricmp(xargv[2], "-d"))
        {
            for (file = cab->files; file; file = file->next, count++)
            {
                RtlCliDisplayString(">%s\n", file->filename);
            }
            RtlCliDisplayString("total %d files.\n", count);
        }
        else
        {
            strcpy(buf, target);
            p = &buf[strlen(buf) - 1];
            if(*p != '\\') *(++p) = '\\';
            p++;
            for (file = cab->files; file; file = file->next, count++)
            {
                strcpy(p, file->filename);
                RtlCliDisplayString(">%s", file->filename);
                if (cabd->extract(cabd, file, buf) == MSPACK_ERR_OK)
                {
                    count_ok++;
                    RtlCliDisplayString("...ok\n");
                }
                else
                {
                    count_err++;
                    RtlCliDisplayString("...error : %d\n", cabd->last_error(cabd));
                    DbgPrint("expand error: %d  %s \n", cabd->last_error(cabd), buf);
                }
            }
            RtlCliDisplayString("total %d files, %d files ok, %d files error.\n", count, count_ok, count_err);

        }
        cabd->close(cabd, cab);
    }
    mspack_destroy_cab_decompressor(cabd);
}