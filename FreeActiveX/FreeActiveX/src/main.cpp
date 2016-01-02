/*****************************************************************************
 * main.cpp: Free ActiveX based on ActiveX control for VLC
 *****************************************************************************
 * Copyright (C) 2005 the VideoLAN team
 * Copyright (C) 2008 http://unick-soft.xost.ru
 *
 * Authors: Damien Fouilleul <Damien.Fouilleul@laposte.net>
 * Modification: Oleg <soft_support@list.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "plug-in/plugin.h"
#include "misc/utils.h"

#include <stdio.h>

#include <comcat.h>
#include <windows.h>
#include <TCHAR.h>
#include <shlwapi.h>

#include <tchar.h>
#define INITGUID
#include <guiddef.h>

using namespace std;

//It is test exmple for create ActiveX without ALT an MFC
#define COMPANY_STR "Your company"
#define PROGRAM_STR "Your ActiveX program"
#define DESCRIPTION "ActiveX Example with out ALT and MFC"

#define THREADING_MODEL "Apartment"
#define MISC_STATUS     "131345"

#define PROGID_STR COMPANY_STR

#define GUID_STRLEN 39

DEFINE_GUID(_CATID_SafeForInitializing, 0x7DD95802, 0x9882, 0x11CF, 0x9F, 0xA9, 0x00,0xAA,0x00,0x6C,0x42,0xC4);
DEFINE_GUID(_CATID_SafeForScripting,    0x7DD95801, 0x9882, 0x11CF, 0x9F, 0xA9, 0x00,0xAA,0x00,0x6C,0x42,0xC4);

static LONG i_class_ref= 0;
static HINSTANCE h_instance= 0;

HMODULE DllGetModule()
{
    return h_instance;
};

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;

    *ppv = NULL;

    if( (CLSID_AXPlugin == rclsid ) )
    {
        VLCPluginClass *plugin = new VLCPluginClass(&i_class_ref, h_instance, rclsid);
        hr = plugin->QueryInterface(riid, ppv);
        plugin->Release();
    }
    return hr;
};

STDAPI DllCanUnloadNow(VOID)
{
    return (0 == i_class_ref) ? S_OK: S_FALSE;
};

static inline HKEY keyCreate(HKEY parentKey, LPCTSTR keyName)
{
    HKEY childKey;
    if( ERROR_SUCCESS == RegCreateKeyEx(parentKey, keyName, 0, NULL,
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &childKey, NULL) )
    {
        return childKey;
    }
    return NULL;
};

static inline HKEY keySet(HKEY hKey, LPCTSTR valueName, const void *s, size_t len, DWORD dwType = REG_SZ)
{
    if( NULL != hKey )
    {
        RegSetValueEx(hKey, valueName, 0, dwType,
            (const BYTE*)s, len);
    }
    return hKey;
};

static inline HKEY keySetDef(HKEY hKey, const void *s, size_t len, DWORD dwType = REG_SZ)
{
    return keySet(hKey, NULL, s, len, dwType);
};

static inline HKEY keySetDef(HKEY hKey, LPCTSTR s)
{
    return keySetDef(hKey, s, sizeof(TCHAR)*(_tcslen(s)+1), REG_SZ);
};

static inline HKEY keyClose(HKEY hKey)
{
    if( NULL != hKey )
    {
        RegCloseKey(hKey);
    }
    return NULL;
};

static void UnregisterProgID(REFCLSID rclsid, unsigned int version)
{
    OLECHAR szCLSID[GUID_STRLEN];

    StringFromGUID2(rclsid, szCLSID, GUID_STRLEN);

    TCHAR progId[sizeof(PROGID_STR)+16];
    _stprintf(progId, TEXT("%s.%u"), TEXT(PROGID_STR), version);

    HKEY hProjIDKey;
    if( ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes"), 0, KEY_WRITE | KEY_WOW64_64KEY, &hProjIDKey) )
    {
        SHDeleteKey(hProjIDKey, progId);
        RegCloseKey(hProjIDKey);
    }

    HKEY hClsIDKey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\CLSID"), 0, KEY_WRITE | KEY_WOW64_64KEY, &hClsIDKey))
    {
        SHDeleteKey(hClsIDKey, (const WCHAR*) szCLSID);
        RegCloseKey(hClsIDKey);
    }
};

STDAPI DllUnregisterServer(VOID)
{
    // unregister type lib from the registry
    UnRegisterTypeLib(LIBID_FREE_AX, 1, 0, LOCALE_NEUTRAL, SYS_WIN32);

    // remove component categories we supports
    ICatRegister *pcr;
    if( SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr)) ) {
        CATID implCategories[] = {
            CATID_Control,
            CATID_PersistsToPropertyBag,
            CATID_InternetAware,
            _CATID_SafeForInitializing,
            _CATID_SafeForScripting,
        };

        pcr->UnRegisterClassImplCategories(CLSID_AXPlugin,
                sizeof(implCategories)/sizeof(CATID), implCategories);
        pcr->Release();
    }

    SHDeleteKey(HKEY_CURRENT_USER, TEXT(PROGID_STR));

    UnregisterProgID(CLSID_AXPlugin, 2);

    return S_OK;
};

static HRESULT RegisterClassID(HKEY hParent, REFCLSID rclsid, unsigned int version, BOOL isDefault, LPCTSTR path,const size_t pathLen)
{
    TCHAR progId[sizeof(PROGID_STR)+16];
    _stprintf(progId, TEXT("%s.%u"), TEXT(PROGID_STR), version);

    TCHAR description[sizeof(DESCRIPTION)+16];
    _stprintf(description, TEXT("%s v%u"), TEXT(DESCRIPTION), version);

    HKEY hClassKey;
	HKEY hClassBase;
    {
        OLECHAR szCLSID[GUID_STRLEN];

        StringFromGUID2(rclsid, szCLSID, GUID_STRLEN);

        HKEY hProgKey = keyCreate(hParent, progId);
        if( NULL != hProgKey )
        {
            // default key value
            keySetDef(hProgKey, description);

            keyClose(keySetDef(keyCreate(hProgKey, TEXT("CLSID")),
                szCLSID,
                sizeof(szCLSID)));

            RegCloseKey(hProgKey);
        }
		if (isDefault)
		{
			hProgKey = keyCreate(hParent, TEXT(PROGID_STR));
			if (NULL != hProgKey)
			{
				// default key value
				keySetDef(hProgKey, description);

				keyClose(keySetDef(keyCreate(hProgKey, TEXT("CLSID")),
					szCLSID,
					sizeof(szCLSID)));

				keyClose(keySetDef(keyCreate(hProgKey, TEXT("CurVer")),
					progId));
			}
		}

		if( ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\CLSID"), 0, KEY_CREATE_SUB_KEY | KEY_WOW64_64KEY, &hClassBase) )
			return SELFREG_E_CLASS;
        hClassKey = keyCreate(hClassBase, (const TCHAR *) szCLSID);
	}

    if( NULL != hClassKey )
    {
        // default key value
        keySetDef(hClassKey, description);

        // Control key value
        keyClose(keyCreate(hClassKey, TEXT("Control")));

        // ToolboxBitmap32 key value
        {
            TCHAR* iconPath = new TCHAR[pathLen + 3];
            memcpy(iconPath, path, sizeof(TCHAR)*pathLen);
            _tcscpy(iconPath+pathLen, TEXT(",1"));
            keyClose(keySetDef(keyCreate(hClassKey,
                TEXT("ToolboxBitmap32")),
                iconPath, sizeof(TCHAR) * (pathLen + 3)));
            delete[] iconPath;
            iconPath = NULL;
        }

        // InprocServer32 key value
        {
            HKEY hSubKey = keySetDef(keyCreate(hClassKey,
                TEXT("InprocServer32")),
                path, sizeof(TCHAR)*(pathLen+1));
            keySet(hSubKey,
                TEXT("ThreadingModel"),
                TEXT(THREADING_MODEL), sizeof(TEXT(THREADING_MODEL)));
            keyClose(hSubKey);
        }

        // MiscStatus key value
        keyClose(keySetDef(keyCreate(hClassKey,
            TEXT("MiscStatus\\1")),
            TEXT(MISC_STATUS), sizeof(TEXT(MISC_STATUS))));

        // Programmable key value
        keyClose(keyCreate(hClassKey, TEXT("Programmable")));

        // ProgID key value
        keyClose(keySetDef(keyCreate(hClassKey,
            TEXT("ProgID")),
            progId));

        // VersionIndependentProgID key value
        keyClose(keySetDef(keyCreate(hClassKey,
            TEXT("VersionIndependentProgID")),
            TEXT(PROGID_STR), sizeof(TEXT(PROGID_STR))));

        // Version key value
        keyClose(keySetDef(keyCreate(hClassKey,
            TEXT("Version")),
            TEXT("1.0")));

        // TypeLib key value
        OLECHAR szLIBID[GUID_STRLEN];

        StringFromGUID2(LIBID_FREE_AX, szLIBID, GUID_STRLEN);

        keyClose(keySetDef(keyCreate(hClassKey,
                TEXT("TypeLib")),
                szLIBID, sizeof(szLIBID)));
 
        RegCloseKey(hClassKey);
    }
    return S_OK;
}

STDAPI DllRegisterServer(VOID)
{
	// Start debugging register
	DebugBreak();

    DllUnregisterServer();

    TCHAR DllPath[MAX_PATH];
    DWORD DllPathLen=GetModuleFileName(h_instance, DllPath, MAX_PATH) ;
    if( 0 == DllPathLen )
        return E_UNEXPECTED;

    HKEY hBaseKey;
	LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes"), 0, KEY_CREATE_SUB_KEY | KEY_WOW64_64KEY, &hBaseKey);
    if( ERROR_SUCCESS != status)
        return SELFREG_E_CLASS;

    RegisterClassID(hBaseKey, CLSID_AXPlugin, 2, TRUE, DllPath, DllPathLen);

    RegCloseKey(hBaseKey);

    // indicate which component categories we support
    ICatRegister *pcr;
    if( SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr)) ) {
        CATID implCategories[] = {
            CATID_Control,
            CATID_PersistsToPropertyBag,
            CATID_InternetAware,
            _CATID_SafeForInitializing,
            _CATID_SafeForScripting,
        };

        pcr->RegisterClassImplCategories(CLSID_AXPlugin,
                sizeof(implCategories)/sizeof(CATID), implCategories);
        pcr->Release();
    }

    // register type lib into the registry
    ITypeLib *typeLib;

    HRESULT result = LoadTypeLibEx((const WCHAR *) DllPath, REGKIND_REGISTER, &typeLib);
    if( SUCCEEDED(result) )
        typeLib->Release();

    return result;
};


STDAPI_(BOOL) DllMain(HANDLE hModule, DWORD fdwReason, LPVOID lpReserved )
{
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
            h_instance = (HINSTANCE)hModule;
            break;

        default:
            break;
    }
    return TRUE;
};


