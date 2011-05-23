#include <precomp.h>

#ifdef INCLUDE_CMD_EXPAND
enum
{
	EXPAND_RENAME  = 0x001,   /* /R */
	EXPAND_DISPLAY = 0x004,   /* /D */
	EXPAND_FILES   = 0x008,   /* /F */
	EXPAND_YES     = 0x010,   /* /Y */
};

INT CommandExpand (LPTSTR param)
{
	/*cmd is the command that was given, in this case it will always be "expand"
	param is whatever is given after the command*/

	LPTSTR *arg = NULL;
	INT args;
	INT i;
	INT   nEvalArgs = 0; /* nunber of evaluated arguments */
	DWORD dwFlags = 0;
	DWORD dwAttrFlags = 0;
	DWORD dwFiles = 0;
	LONG ch;
	TCHAR szOrginalArg[MAX_PATH];

	/*checks the first two chars of param to see if it is /?
	this however allows the following command to not show help
	"expand frog.cab /?" */

    if (!StringsLoaded)
    {
            LoadStrings();
    }

	if (!_tcsncmp (param, _T("/?"), 2))
	{
		//ConOutResPaging(TRUE,STRING_DEL_HELP1);
		return 0;
	}

	nErrorLevel = 0;

	arg = split (param, &args, FALSE);

	if (args == 0)
	{
		/* only command given */
		error_req_param_missing ();
		freep (arg);
		return 1;
	}
	/* check for options anywhere in command line */
	for (i = 0; i < args; i++)
	{
		if (*arg[i] == _T('-'))
		{
			/*found a command, but check to make sure it has something after it*/
			if (_tcslen (arg[i]) >= 2)
			{
				ch = _totupper (arg[i][1]);
				if (ch == _T('R'))
				{
					dwFlags |= EXPAND_RENAME;
				}
				else if (ch == _T('D'))
				{
					dwFlags |= EXPAND_DISPLAY;
				}
				else if (ch == _T('F'))
				{
					dwFlags |= EXPAND_FILES;
				}
				else if (ch == _T('Y'))
				{
					dwFlags |= EXPAND_YES;
				}

			}

			nEvalArgs++;
		}
	}

	/* there are only options on the command line --> error!!!
	there is the same number of args as there is flags, so none of the args were filenames*/
	if (args == nEvalArgs)
	{
		error_req_param_missing ();
		freep (arg);
		return 1;
	}

	/* check for filenames anywhere in command line */
	for (i = 0; i < args && !(dwFiles & 0x80000000); i++)
	{

        /*this checks to see if it isnt a flag, if it isnt, we assume it is a file name*/
		if((*arg[i] == _T('/')) || (*arg[i] == _T('-')))
			continue;

		/* We want to make a copies of the argument */


	freep (arg);

	/*Based on MS cmd, we only tell what files are being deleted when /S is used */
	if (dwFlags & DEL_TOTAL)
	{
                dwFiles &= 0x7fffffff;
		if (dwFiles < 2)
		{
                        ConOutResPrintf(STRING_DEL_HELP3, dwFiles);
		}
		else
		{
			ConOutResPrintf(STRING_DEL_HELP4, dwFiles);
		}
	}

	return 0;



}
#endif