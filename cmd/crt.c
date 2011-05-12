#include <precomp.h>

INT
FormatDate(TCHAR *lpDate, LPSYSTEMTIME dt, BOOL b4Digit)
{
	/* Format date */
	WORD wYear = b4Digit ? dt->wYear : dt->wYear%100;
	switch (nDateFormat)
	{
		case 0: /* mmddyy */
		default:
			return _stprintf(lpDate, _T("%02d%c%02d%c%0*d"),
					dt->wMonth, cDateSeparator,
					dt->wDay, cDateSeparator,
					b4Digit?4:2, wYear);
			break;

		case 1: /* ddmmyy */
			return _stprintf(lpDate, _T("%02d%c%02d%c%0*d"),
					dt->wDay, cDateSeparator, dt->wMonth,
					cDateSeparator, b4Digit?4:2, wYear);
			break;

		case 2: /* yymmdd */
			return _stprintf(lpDate, _T("%0*d%c%02d%c%02d"),
					b4Digit?4:2, wYear, cDateSeparator,
					dt->wMonth, cDateSeparator, dt->wDay);
			break;
	}
}

INT
FormatTime(TCHAR *lpTime, LPSYSTEMTIME dt)
{
	/* Format Time */
	switch (nTimeFormat)
	{
		case 0: /* 12 hour format */
		default:
			return _stprintf(lpTime,_T("%02d%c%02u %cM"),
					(dt->wHour == 0 ? 12 : (dt->wHour <= 12 ? dt->wHour : dt->wHour - 12)),
					cTimeSeparator,
					 dt->wMinute, (dt->wHour <= 11 ? _T('A') : _T('P')));
			break;

		case 1: /* 24 hour format */
			return _stprintf(lpTime, _T("%02d%c%02u"),
					dt->wHour, cTimeSeparator, dt->wMinute);
			break;
	}
}