#include "precomp.h"

BOOL bExit = FALSE;       /* indicates EXIT was typed */
BOOL bCanExit = TRUE;     /* indicates if this shell is exitable */
BOOL bIgnoreEcho = FALSE; /* Set this to TRUE to prevent a newline, when executing a command */
INT  nErrorLevel = 0;     /* Errorlevel of last launched external program */
CRITICAL_SECTION ChildProcessRunningLock;
BOOL bDisableBatchEcho = FALSE;
DWORD dwChildProcessId = 0;
LPTSTR lpOriginalEnvironment;
HANDLE CMD_ModuleHandle;
extern BOOLEAN EchoStatus;
static VOID GetCmdLineCommand(TCHAR *commandline, TCHAR *ptr)
{
	TCHAR *LastQuote;

	while (_istspace(*ptr))
		ptr++;

	/* Remove leading quote, find final quote */
	if (*ptr == _T('"') &&
	    (LastQuote = _tcsrchr(++ptr, _T('"'))) != NULL)
	{
		TCHAR *Space;
		*LastQuote = _T('\0');
		for (Space = ptr + 1; Space < LastQuote; Space++)
		{
			if (_istspace(*Space))                         /* Rule 4 */
			{
//				if (!AlwaysStrip &&                        /* Rule 1 */
//				    !_tcspbrk(ptr, _T("\"&<>@^|")) &&      /* Rules 2, 3 */
//				    SearchForExecutable(ptr, commandline)) /* Rule 5 */
//				{
//					*LastQuote = _T('"');
//					_tcscpy(commandline, ptr - 1);
//					return;
//				}
				break;
			}
		}

		_tcscpy(commandline, ptr);
		_tcscpy(&commandline[LastQuote - ptr], LastQuote + 1);
		return;
	}

	_tcscpy(commandline, ptr);
}

static VOID Initialize()
{
	HMODULE NtDllModule;
	TCHAR commandline[CMDLINE_LENGTH];
	TCHAR ModuleName[MAX_PATH + 1];
	TCHAR lpBuffer[2];
	INT nExitCode;
	TCHAR *ptr, *cmdLine, option = 0;

	if (GetEnvironmentVariable(_T("PROMPT"),lpBuffer, sizeof(lpBuffer) / sizeof(lpBuffer[0])) == 0)
	    SetEnvironmentVariable (_T("PROMPT"), _T("$P$G"));

	/* Set COMSPEC environment variable */
	if (0 != GetModuleFileName (NULL, ModuleName, MAX_PATH + 1))
	{
		ModuleName[MAX_PATH] = _T('\0');
		SetEnvironmentVariable (_T("COMSPEC"), ModuleName);
	}

	cmdLine = GetCommandLine();
	TRACE ("[command args: %s]\n", cmdLine);

	for (ptr = cmdLine; *ptr; ptr++)
	{
		if (*ptr == _T('/'))
		{
			option = (TCHAR)_totupper(ptr[1]);
			if (option == _T('C') || option == _T('K') || option == _T('R'))
			{
				/* Remainder of command line is a command to be run */
				break;
			}
			else if (option == _T('Q'))
			{
				EchoStatus = FALSE;
			}
		}
	}
	if (*ptr)
	{
		/* Do the /C or /K command */
		GetCmdLineCommand(commandline, &ptr[2]);
		//nExitCode = ParseCommandLine(commandline);
		if (option != _T('K'))
		{
			nErrorLevel = nExitCode;
			bExit = TRUE;
		}
	}
}

NTSTATUS __cdecl main(INT argc, PCHAR argv[], PCHAR envp[], ULONG DebugFlag OPTIONAL)
{
  PPEB Peb = NtCurrentPeb();
  NTSTATUS Status;
  PCHAR Command;
  DbgPrint("!!!Native Shell START....................................................\n");
  DisplayString("NativeShell [Version 0.0.0.1 Build 2011-5-12]");
  DisplayString("Welcome to NativeShell world!");
  while (TRUE)
    {
      PrintPrompt();
      Command = ReadLine();
    }
  DbgPrint("!!!Native Shell Terminate...................................................\n");
  NtTerminateProcess( NtCurrentProcess(), 0 );
  return STATUS_SUCCESS;
}
