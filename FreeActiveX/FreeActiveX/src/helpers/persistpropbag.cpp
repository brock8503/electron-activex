/*****************************************************************************
 * persistpropbag.cpp: Free ActiveX based on ActiveX control for VLC
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

#include "../plug-in/plugin.h"
#include "persistpropbag.h"

#include "../misc/utils.h"
#include "oleobject.h"

using namespace std;

STDMETHODIMP VLCPersistPropertyBag::GetClassID(LPCLSID pClsID)
{
    if( NULL == pClsID )
        return E_POINTER;

    *pClsID = _p_instance->getClassID();

    return S_OK;
};

STDMETHODIMP VLCPersistPropertyBag::InitNew(void)
{
    return _p_instance->onInit();
};

STDMETHODIMP VLCPersistPropertyBag::Load(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog)
{
    HRESULT hr = _p_instance->onInit();
    if( FAILED(hr) )
        return hr;

    if( NULL == pPropBag )
        return E_INVALIDARG;

    VARIANT value;

    SIZEL size = _p_instance->getExtent();
    V_VT(&value) = VT_I4;
    if( S_OK == pPropBag->Read(OLESTR("extentwidth"), &value, pErrorLog) )
    {
         size.cx = V_I4(&value);
        VariantClear(&value);
    }
    V_VT(&value) = VT_I4;
    if( S_OK == pPropBag->Read(OLESTR("extentheight"), &value, pErrorLog) )
    {
         size.cy = V_I4(&value);
        VariantClear(&value);
    }
    _p_instance->setExtent(size);

    V_VT(&value) = VT_I4;
    if( S_OK == pPropBag->Read(OLESTR("backcolor"), &value, pErrorLog) )
    {
        _p_instance->setBackColor(V_I4(&value));
        VariantClear(&value);
    }
    else
    {
        /*
        ** try alternative syntax
        */
        V_VT(&value) = VT_BSTR;
        if( S_OK == pPropBag->Read(OLESTR("bgcolor"), &value, pErrorLog) )
        {
            long backcolor;
            if( swscanf(V_BSTR(&value), L"#%lX", &backcolor) )
            {
                _p_instance->setBackColor(backcolor);
            }
            VariantClear(&value);
        }
    }

    return _p_instance->onLoad();
};

STDMETHODIMP VLCPersistPropertyBag::Save(LPPROPERTYBAG pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties)
{
    if( NULL == pPropBag )
        return E_INVALIDARG;

    VARIANT value;

    VariantInit(&value);

    SIZEL size = _p_instance->getExtent();
    V_VT(&value) = VT_I4;
    V_I4(&value) = size.cx;
    pPropBag->Write(OLESTR("ExtentWidth"), &value);
    V_I4(&value) = size.cy;
    pPropBag->Write(OLESTR("ExtentHeight"), &value);

    V_VT(&value) = VT_I4;
    V_I4(&value) = _p_instance->getBackColor();
    pPropBag->Write(OLESTR("BackColor"), &value);
    VariantClear(&value);

    if( fClearDirty )
        _p_instance->setDirty(FALSE);

    return S_OK;
};
