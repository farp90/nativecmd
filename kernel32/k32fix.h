#define _ANONYMOUS_UNION
//++winbase.h

#define SYMBOLIC_LINK_FLAG_DIRECTORY 0x1

HANDLE WINAPI CreateEventExA(LPSECURITY_ATTRIBUTES,LPCSTR,DWORD,DWORD);
HANDLE WINAPI CreateEventExW(LPSECURITY_ATTRIBUTES,LPCWSTR,DWORD,DWORD);

#define CREATE_EVENT_MANUAL_RESET   0x1
#define CREATE_EVENT_INITIAL_SET    0x2
#define CREATE_MUTEX_INITIAL_OWNER  0x1
#define CREATE_WAITABLE_TIMER_MANUAL_RESET  0x1
#define SRWLOCK_INIT    RTL_SRWLOCK_INIT
#define CONDITION_VARIABLE_INIT RTL_CONDITION_VARIABLE_INIT
#define CONDITION_VARIABLE_LOCKMODE_SHARED  RTL_CONDITION_VARIABLE_LOCKMODE_SHARED

BOOL WINAPI GetFileAttributesByHandle(HANDLE,LPDWORD,DWORD);
DWORD WINAPI GetFinalPathNameByHandleA(HANDLE,LPSTR,DWORD,DWORD);
DWORD WINAPI GetFinalPathNameByHandleW(HANDLE,LPWSTR,DWORD,DWORD);

#define MAX_RESTART_CMD_LINE 0x800
#define RESTART_CYCLICAL 0x1
#define RESTART_NOTIFY_SOLUTION 0x2
#define RESTART_NOTIFY_FAULT 0x4
#define VOLUME_NAME_DOS 0x0
#define VOLUME_NAME_GUID 0x1
#define VOLUME_NAME_NT 0x2
#define VOLUME_NAME_NONE 0x4
#define FILE_NAME_NORMALIZED 0x0
#define FILE_NAME_OPENED 0x8
#define FILE_SKIP_COMPLETION_PORT_ON_SUCCESS 0x1
#define FILE_SKIP_SET_EVENT_ON_HANDLE 0x2

typedef enum _FILE_ID_TYPE {
	FileIdType,
	MaximumFileIdType
} FILE_ID_TYPE, *PFILE_ID_TYPE;

typedef struct _FILE_ID_DESCRIPTOR {
	DWORD dwSize;
	FILE_ID_TYPE Type;
	_ANONYMOUS_UNION union {
		LARGE_INTEGER FileID;
	} DUMMYUNIONNAME;
} FILE_ID_DESCRIPTOR, *LPFILE_ID_DESCRIPTOR;

HANDLE WINAPI CreateMutexExA(LPSECURITY_ATTRIBUTES,LPCSTR,DWORD,DWORD);
HANDLE WINAPI CreateMutexExW(LPSECURITY_ATTRIBUTES,LPCWSTR,DWORD,DWORD);

HANDLE WINAPI CreateSemaphoreExA(LPSECURITY_ATTRIBUTES,LONG,LONG,LPCSTR,DWORD,DWORD);
HANDLE WINAPI CreateSemaphoreExW(LPSECURITY_ATTRIBUTES,LONG,LONG,LPCWSTR,DWORD,DWORD);

ULONGLONG WINAPI GetTickCount64(VOID);

HANDLE WINAPI CreateWaitableTimerExA(LPSECURITY_ATTRIBUTES,LPCSTR,DWORD,DWORD);
HANDLE WINAPI CreateWaitableTimerExW(LPSECURITY_ATTRIBUTES,LPCWSTR,DWORD,DWORD);

//--winbase.h

//++winnls.h

#define LOCALE_RETURN_GENITIVE_NAMES  0x10000000   //Flag to return the Genitive forms of month names
#define LOCALE_ALLOW_NEUTRAL_NAMES    0x08000000   //Flag to allow returning neutral names/lcids for name conversion


#define LOCALE_ILANGUAGE              0x00000001   // language id, LOCALE_SNAME preferred

#define LOCALE_SNAME                  0x0000005c   // locale name (ie: en-us)
//--winnls.h

//++windef.h
#if 1 // needed by shlwapi.h
#ifndef __ms_va_list
# if defined(__x86_64__)
#  define __ms_va_list __builtin_ms_va_list
#  define __ms_va_start(list,arg) __builtin_ms_va_start(list,arg)
#  define __ms_va_end(list) __builtin_ms_va_end(list)
# else
#  define __ms_va_list va_list
#  define __ms_va_start(list,arg) va_start(list,arg)
#  define __ms_va_end(list) va_end(list)
# endif
#endif
#endif
#undef NDEBUG


#if _WIN32_WINNT < 0x0502
WINBASEAPI
DWORD
WINAPI
GetDllDirectoryA(
    __in DWORD nBufferLength,
    __out_ecount_part_opt(nBufferLength, return + 1) LPSTR lpBuffer
    );
WINBASEAPI
DWORD
WINAPI
GetDllDirectoryW(
    __in DWORD nBufferLength,
    __out_ecount_part_opt(nBufferLength, return + 1) LPWSTR lpBuffer
    );
#define RtlInitAnsiStringEx _RtlInitAnsiStringEx
#define RtlAllocateActivationContextStack _RtlAllocateActivationContextStack
NTSTATUS
NTAPI
_RtlInitAnsiStringEx(IN OUT PANSI_STRING DestinationString,
                    IN PCSZ SourceString);
NTSTATUS
NTAPI
_RtlAllocateActivationContextStack(IN PVOID *Context);
#endif
