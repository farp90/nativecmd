#include <k32.h>
//#include <ndkfix.h>

#undef HeapAlloc
#undef HeapReAlloc
#undef HeapFree
#if 0
VOID
WINAPI
DebugBreak(
    VOID
)
{
    DbgBreakPoint();
}

__out_opt
PVOID
WINAPI
DecodePointer(
    PVOID Pointer
)
{
    return RtlDecodePointer(Pointer);
}

__out_opt
PVOID
WINAPI
DecodeSystemPointer(
    PVOID Pointer
)
{
    return RtlDecodeSystemPointer(Pointer);
}

__out_opt
PVOID
WINAPI
EncodePointer(
    PVOID Pointer
)
{
    return RtlEncodePointer(Pointer);
}

__out_opt
PVOID
WINAPI
EncodeSystemPointer(
    PVOID Pointer
)
{
    return RtlEncodeSystemPointer(Pointer);
}
#endif

VOID
WINAPI
DeleteCriticalSection (
    LPCRITICAL_SECTION CriticalSection
)
{
    RtlDeleteCriticalSection(CriticalSection);
}
VOID
WINAPI
EnterCriticalSection(
    LPCRITICAL_SECTION CriticalSection
)
{
    RtlEnterCriticalSection(CriticalSection);
}

__bcount(dwBytes)
LPVOID
WINAPI
HeapAlloc(
    HANDLE HeapHandle,
    DWORD Flags,
    SIZE_T Size
)
{
    return RtlAllocateHeap(
        HeapHandle,
        Flags,
        Size
    );
}

BOOL
WINAPI
HeapFree(
    HANDLE HeapHandle,
    DWORD Flags,
    LPVOID P
)
{
    return RtlFreeHeap(
        HeapHandle,
        Flags,
        P
    );
}

__bcount(dwBytes)
LPVOID
WINAPI
HeapReAlloc(
    HANDLE Heap,
    DWORD Flags,
    LPVOID Ptr,
    SIZE_T Size
)
{
    return RtlReAllocateHeap(
        Heap,
        Flags,
        Ptr,
        Size
    );
}

SIZE_T
WINAPI
HeapSize(
    HANDLE HeapHandle,
    DWORD Flags,
    LPCVOID MemoryPointer
)
{
    return RtlSizeHeap(
        HeapHandle,
        Flags,
        (PVOID)MemoryPointer
    );
}


VOID
WINAPI
LeaveCriticalSection(LPCRITICAL_SECTION CriticalSection)
{
    RtlLeaveCriticalSection(
        CriticalSection
    );
}

BOOL
WINAPI
TryEnterCriticalSection(
    LPCRITICAL_SECTION CriticalSection
)
{
    return RtlTryEnterCriticalSection(
        CriticalSection
    );
}
#if 0
__out_opt
PVOID
WINAPI
AddVectoredExceptionHandler (
    ULONG First,
    PVECTORED_EXCEPTION_HANDLER Handler
    )
{
    return RtlAddVectoredExceptionHandler(First, Handler);
}

VOID
WINAPI
InitializeSListHead (
    PSLIST_HEADER ListHead
    )
{
    RtlInitializeSListHead(ListHead);
}

PSLIST_ENTRY
WINAPI
InterlockedFlushSList (
    PSLIST_HEADER ListHead
    )
{
    return RtlInterlockedFlushSList (
        ListHead
        );
}

PSLIST_ENTRY
WINAPI
InterlockedPopEntrySList (
    PSLIST_HEADER ListHead
    )
{
    return RtlInterlockedPopEntrySList (
        ListHead
        );
}

PSLIST_ENTRY
WINAPI
InterlockedPushEntrySList (
    PSLIST_HEADER ListHead,
    PSLIST_ENTRY ListEntry
    )
{
    return RtlInterlockedPushEntrySList (
        ListHead,
        ListEntry
        );
}

USHORT
WINAPI
QueryDepthSList (
    PSLIST_HEADER ListHead
    )

{
    return RtlQueryDepthSList (
        ListHead
        );
}

ULONG
WINAPI
RemoveVectoredExceptionHandler (
    PVOID Handle
    )
{
    return RtlRemoveVectoredExceptionHandler (
        Handle
        );
}

DWORD
WINAPI
SetCriticalSectionSpinCount(
    LPCRITICAL_SECTION lpCriticalSection,
    DWORD dwSpinCount
    )
{
    return RtlSetCriticalSectionSpinCount(
        lpCriticalSection,
        dwSpinCount
        );
}
#endif
#if (_WIN32_WINNT < 0x0502)
NTSTATUS
NTAPI
RtlInitAnsiStringEx(IN OUT PANSI_STRING DestinationString,
                    IN PCSZ SourceString)
{
    ULONG DestSize;

    if(SourceString)
    {
        DestSize = strlen(SourceString);
        if (DestSize >= 0xFFFF) return STATUS_NAME_TOO_LONG;
        DestinationString->Length = (USHORT)DestSize;
        DestinationString->MaximumLength = (USHORT)DestSize + sizeof(CHAR);
    }
    else
    {
        DestinationString->Length = 0;
        DestinationString->MaximumLength = 0;
    }

    DestinationString->Buffer = (PCHAR)SourceString;
    return STATUS_SUCCESS;

}

NTSTATUS
NTAPI
_RtlAllocateActivationContextStack(IN PVOID *Context)
{
    PACTIVATION_CONTEXT_STACK ContextStack;
    ContextStack = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, sizeof (ACTIVATION_CONTEXT_STACK) );
    if (!ContextStack)
    {
        return STATUS_NO_MEMORY;
    }

    ContextStack->ActiveFrame = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(RTL_ACTIVATION_CONTEXT_STACK_FRAME));
    if (!ContextStack->ActiveFrame) return STATUS_NO_MEMORY;

    *Context = ContextStack;

    /* FIXME: Documentation on MSDN reads that activation contexts are only created
              for modules that have a valid manifest file or resource */
    //actctx_init();

    return STATUS_SUCCESS;
}


#endif
BOOL
WINAPI
MessageBeep(UINT uType)
{
    return 0;
}