/*
 * Copyright (c) 2008, KJK::Hyperion
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of the ReactOS Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define _CRTIMP
#include <k32.h>
#define ROUND_DOWN(n, align) \
    (((ULONG)n) & ~((align) - 1l))

#define ROUND_UP(n, align) \
    ROUND_DOWN(((ULONG)n) + (align) - 1, (align))

/* round to 16 bytes + alloc at minimum 16 bytes */
#define ROUND_SIZE(size) (max(16, ROUND_UP(size, 16)))

extern "C"
{

void* __cdecl malloc(size_t _size)
{
   size_t nSize = ROUND_SIZE(_size);

   if (nSize<_size)
       return NULL;

   return HeapAlloc(GetProcessHeap(), 0, nSize);
}

void __cdecl free(void* _ptr)
{
   HeapFree(GetProcessHeap(),0,_ptr);
}

void* __cdecl calloc(size_t _nmemb, size_t _size)
{
   size_t nSize = _nmemb * _size;
   size_t cSize = ROUND_SIZE(nSize);

   if ( (_nmemb > ((size_t)-1 / _size))  || (cSize<nSize))
      return NULL;

   return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cSize );
}

void* __cdecl realloc(void* _ptr, size_t _size)
{
   size_t nSize;

   if (_ptr == NULL)
      return malloc(_size);

   if (_size == 0)
   {
   	   free(_ptr);
       return NULL;
   }

   nSize = ROUND_SIZE(_size);

   /* check for integer overflow */
   if (nSize<_size)
       return NULL;

   return HeapReAlloc(GetProcessHeap(), 0, _ptr, nSize);
}

void* __cdecl _expand(void* _ptr, size_t _size)
{
   size_t nSize;

   nSize = ROUND_SIZE(_size);

   if (nSize<_size)
       return NULL;

   return HeapReAlloc(GetProcessHeap(), HEAP_REALLOC_IN_PLACE_ONLY, _ptr, nSize);
}

size_t __cdecl _msize(void* _ptr)
{
   return HeapSize(GetProcessHeap(), 0, _ptr);
}

int __cdecl	_heapchk(void)
{
	if (!HeapValidate(GetProcessHeap(), 0, NULL))
		return -1;
	return 0;
}

int __cdecl	_heapmin(void)
{
	if (!HeapCompact(GetProcessHeap(), 0))
		return -1;
	return 0;
}

int __cdecl	_heapset(unsigned int unFill)
{
	if (_heapchk() == -1)
		return -1;
	return 0;

}
int __cdecl _purecall()
{
	FatalAppExitW(0, L"pure virtual call");
	FatalExit(0);
	return 0;
}

void _assert()
{
	FatalAppExitW(0, L"assertion failed");
	FatalExit(0);
}
}
extern "C++"
{
void * __cdecl operator new(size_t size)
{
	return malloc(size);
}


void __cdecl operator delete(void * memory)
{
	free(memory);
}
}
// EOF
