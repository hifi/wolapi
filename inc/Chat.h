/*
 * Copyright (c) 2011 Toni Spets <toni.spets@iki.fi>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <wolapi.h>

#ifndef _CHAT_H_
#define _CHAT_H_

/* Chat Class */
extern const GUID CLSID_Chat;

typedef struct _Chat        Chat;
typedef struct _ChatVtbl    ChatVtbl;

struct _Chat
{
    ChatVtbl    *lpVtbl;

    int         ref;
};

struct _ChatVtbl
{
    /* IUnknown */
    HRESULT(__stdcall *QueryInterface)              (Chat *, const IID* const riid, LPVOID * ppvObj);
    ULONG(__stdcall *AddRef)                        (Chat *);
    ULONG(__stdcall *Release)                       (Chat *);

    /* IClassFactory */
    HRESULT(__stdcall *CreateInstance)              (Chat *, IUnknown *, REFIID, void **);
    HRESULT(__stdcall *LockServer)                  (Chat *, BOOL);
};

#define Chat_CreateInstance(T,a,b,c) (T)->lpVtbl->CreateInstance(T,a,b,c)

Chat* Chat_New();

#endif
