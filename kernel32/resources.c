#define _USER32_
#include <k32.h>
/*
 * @implemented (Synced with Wine 08.01.2009)
 */
int
WINAPI
LoadStringA(HINSTANCE instance, UINT resource_id, LPSTR buffer, INT buflen)
{
    HGLOBAL hmem;
    HRSRC hrsrc;
    DWORD retval = 0;

    if (!buflen) return -1;

    /* Use loword (incremented by 1) as resourceid */
    if ((hrsrc = FindResourceW( instance, MAKEINTRESOURCEW((LOWORD(resource_id) >> 4) + 1),
                                (LPWSTR)RT_STRING )) &&
        (hmem = LoadResource( instance, hrsrc )))
    {
        const WCHAR *p = LockResource(hmem);
        unsigned int id = resource_id & 0x000f;

        while (id--) p += *p + 1;

        RtlUnicodeToMultiByteN( buffer, buflen - 1, &retval, (PWSTR)(p + 1), *p * sizeof(WCHAR) );
    }
    buffer[retval] = 0;
    return retval;
}


/*
 * @implemented (Synced with Wine 08.01.2009)
 */
int
WINAPI
LoadStringW(HINSTANCE instance, UINT resource_id, LPWSTR buffer, INT buflen)
{
    HGLOBAL hmem;
    HRSRC hrsrc;
    WCHAR *p;
    int string_num;
    int i;

    if(buffer == NULL)
        return 0;

    /* Use loword (incremented by 1) as resourceid */
    hrsrc = FindResourceW( instance, MAKEINTRESOURCEW((LOWORD(resource_id) >> 4) + 1),
                           (LPWSTR)RT_STRING );
    if (!hrsrc) return 0;
    hmem = LoadResource( instance, hrsrc );
    if (!hmem) return 0;

    p = LockResource(hmem);
    string_num = resource_id & 0x000f;
    for (i = 0; i < string_num; i++)
    p += *p + 1;

    /*if buflen == 0, then return a read-only pointer to the resource itself in buffer
    it is assumed that buffer is actually a (LPWSTR *) */
    if(buflen == 0)
    {
        *((LPWSTR *)buffer) = p + 1;
        return *p;
    }

    i = min(buflen - 1, *p);
    if (i > 0) {
    memcpy(buffer, p + 1, i * sizeof (WCHAR));
        buffer[i] = 0;
    } else {
    if (buflen > 1) {
            buffer[0] = 0;
        return 0;
    }
    }

    return i;
}