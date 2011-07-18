@ECHO OFF
SET MAJOR=0
SET MINOR=0
SET PATCH=1
SET TYPE=M2

FOR /F "tokens=1,2,3 delims=-/: " %%i IN ("%date%") DO (
    SET BUILD_DATE=%%i%%j%%k
)
IF NOT DEFINED BUILD_DATE (
	SET /P BUILD_DATE=ºê´íÎó..ÇëÖ¸¶¨:
)
PUSHD ..\inc\reactos

ECHO Generating buildno.h ...
IF NOT EXIST buildno.old.h COPY buildno.h buildno.old.h >NUL
ECHO.#ifndef _INC_REACTOS_BUILDNO				>buildno.h
ECHO.#define _INC_REACTOS_BUILDNO				>>buildno.h
ECHO.#define KERNEL_VERSION_BUILD	%BUILD_DATE%		>>buildno.h
ECHO.#define KERNEL_VERSION_BUILD_HEX	0x0			>>buildno.h
ECHO.#define KERNEL_VERSION_BUILD_STR	"%BUILD_DATE%"		>>buildno.h
ECHO.#define KERNEL_VERSION_BUILD_RC	"%BUILD_DATE%\0"	>>buildno.h
ECHO.#define KERNEL_RELEASE_RC	"%MAJOR%.%MINOR%.%PATCH%\0"	>>buildno.h
ECHO.#define KERNEL_RELEASE_STR	"%MAJOR%.%MINOR%.%PATCH%"	>>buildno.h
ECHO.#define KERNEL_VERSION_RC	"%MAJOR%.%MINOR%.%PATCH%\0"	>>buildno.h
ECHO.#define KERNEL_VERSION_STR	"%MAJOR%.%MINOR%.%PATCH%"	>>buildno.h
ECHO.#define REACTOS_DLL_VERSION_MAJOR %MAJOR%	>>buildno.h
ECHO.#define REACTOS_DLL_RELEASE_RC	"%MAJOR%.%MINOR%.%PATCH%\0"	>>buildno.h
ECHO.#define REACTOS_DLL_RELEASE_STR	"%MAJOR%.%MINOR%.%PATCH%"	>>buildno.h
ECHO.#define REACTOS_DLL_VERSION_RC	"%MAJOR%.%MINOR%.%PATCH%\0"	>>buildno.h
ECHO.#define REACTOS_DLL_VERSION_STR	"%MAJOR%.%MINOR%.%PATCH%"	>>buildno.h
ECHO.#define REACTOS_DLL_VERSION_STR	"%MAJOR%.%MINOR%.%PATCH%"	>>buildno.h
ECHO.#endif	>>buildno.h

ECHO Generating version.h ...
IF NOT EXIST version.old.h COPY version.h version.old.h >NUL
ECHO.#ifndef __VERSION_H	>version.h
ECHO.#define __VERSION_H	>>version.h
ECHO.#define KERNEL_VERSION_MAJOR        %MAJOR%	>>version.h
ECHO.#define KERNEL_VERSION_MINOR        %MINOR%	>>version.h
ECHO.#define KERNEL_VERSION_PATCH_LEVEL  %PATCH%	>>version.h
ECHO.#define COPYRIGHT_YEAR              "%date:~0,4%"	>>version.h
ECHO.#define KERNEL_VERSION_BUILD_TYPE   L"%TYPE%"	>>version.h
ECHO.#endif	>>version.h

POPD
SET TYPE=fre
CALL BUILD.BAT
