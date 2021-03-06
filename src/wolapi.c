/*
 * Copyright (c) 2011,2012 Toni Spets <toni.spets@iki.fi>
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
#include <stdio.h>

/* unimplemented IIDs */

/* {925CDEDE-71B9-11D1-B1C5-006097176556} */
const GUID IID_IRTPatcher         = {0x925CDEDE,0x71B9,0x11D1,{0xB1,0xC5,0x00,0x60,0x97,0x17,0x65,0x56}};

/* {925CDEE3-71B9-11D1-B1C5-006097176556} */
const GUID IID_IRTPatcherEvent    = {0x925CDEE3,0x71B9,0x11D1,{0xB1,0xC5,0x00,0x60,0x97,0x17,0x65,0x56}};

/* {0BF5FCEB-9F03-11D1-9DC7-006097C54321) */
const GUID IID_IDownload          = {0x0BF5FCEB,0x9F03,0x11D1,{0x9D,0xC7,0x00,0x60,0x97,0xC5,0x43,0x21}};

/* {6869E99D-9FB4-11D1-9DC8-006097C54321) */
const GUID IID_IDownloadEvent     = {0x6869E99D,0x9FB4,0x11D1,{0x9D,0xC8,0x00,0x60,0x97,0xC5,0x43,0x21}};

/* {8B938190-EF3F-11D1-9808-00609706FA0C} */
const GUID IID_IChat2             = {0x8B938190,0xEF3F,0x11D1,{0x98,0x08,0x00,0x60,0x97,0x06,0xFA,0x0C}};

/* {8B938192-EF3F-11D1-9808-00609706FA0C} */
const GUID IID_IChat2Event        = {0x8B938192,0xEF3F,0x11D1,{0x98,0x08,0x00,0x60,0x97,0x06,0xFA,0x0C}};

const char *str_GUID(REFGUID riid)
{
    static char buf[64];
    sprintf(buf, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            (unsigned int)riid->Data1, riid->Data2, riid->Data3,
            riid->Data4[0], riid->Data4[1], riid->Data4[2], riid->Data4[3],
            riid->Data4[4], riid->Data4[5], riid->Data4[6], riid->Data4[7]);
    return (const char*)buf;
}

char *wol_strdup(const char *in)
{
    int len = strlen(in);
    char *out = malloc(len+1);
    memcpy(out, in, len);
    out[len] = '\0';
    return out;
}

#if !_DEBUG
int dprintf(const char *fmt, ...)
{
    return 0;
}
#endif

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    dprintf("DllGetClassObject(irclsid={%s}, riid=%p, ppv=%p)\n", str_GUID(rclsid), riid, ppv);

    dprintf(" riid = {%s}\n", str_GUID(riid));

    if (IsEqualCLSID(rclsid, &CLSID_Chat))
    {
        dprintf(" Chat Class requested\n");
        *ppv = (LPVOID)Chat_New();
        return S_OK;
    }
    else if (IsEqualCLSID(rclsid, &CLSID_NetUtil))
    {
        dprintf(" NetUtil Class requested\n");
        *ppv = (LPVOID)NetUtil_New();
        return S_OK;
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

static HRESULT _CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv)
{
    dprintf("CoCreateInstance(irclsid={%s}, pUnkOuter=%p, dwClsContext=%08X, riid=%p, ppv=%p)\n", str_GUID(rclsid), pUnkOuter, dwClsContext, riid, ppv);

    if (IsEqualIID(riid, &IID_IChat))
    {
        dprintf(" IChat interface requested, returning a new one\n");
        *ppv = IChat_New();
        return S_OK;
    }

    if (IsEqualIID(riid, &IID_INetUtil))
    {
        dprintf(" IChat interface requested, returning a new one\n");
        *ppv = INetUtil_New();
        return S_OK;
    }

    return DllGetClassObject(rclsid, riid, ppv);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        int *p_cocreate = (int *)0x005E6544;
        if (*p_cocreate)
        {
            printf("wolapi: injecting to RA 3.03\n");
            *p_cocreate = (int)_CoCreateInstance;
        }
    }

    return TRUE;
}
