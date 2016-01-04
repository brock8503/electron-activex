

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Jan 02 16:06:51 2016
 */
/* Compiler settings for src\resource\axexample.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_FREE_AX,0x96B4582E,0x74DF,0x49a0,0xB3,0x8E,0x49,0x18,0xE3,0xDB,0xBA,0xB3);


MIDL_DEFINE_GUID(IID, IID_IAXControl,0xC9958507,0xAA21,0x46a8,0x95,0xA6,0xF1,0xFC,0xA1,0x89,0x71,0xF1);


MIDL_DEFINE_GUID(IID, DIID_DAXEvents,0x75B8DD70,0x9BB2,0x41ab,0x8A,0x0D,0xFA,0xBF,0xDA,0x61,0x6C,0x0B);


MIDL_DEFINE_GUID(CLSID, CLSID_AXPlugin,0xF773B261,0x8DD4,0x45cb,0xA8,0x61,0xF8,0xAA,0x2A,0x7A,0xEE,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



