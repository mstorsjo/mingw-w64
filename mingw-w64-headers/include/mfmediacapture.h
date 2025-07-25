/*** Autogenerated by WIDL 10.12 from include/mfmediacapture.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __mfmediacapture_h__
#define __mfmediacapture_h__

/* Forward declarations */

#ifndef __IAdvancedMediaCaptureInitializationSettings_FWD_DEFINED__
#define __IAdvancedMediaCaptureInitializationSettings_FWD_DEFINED__
typedef interface IAdvancedMediaCaptureInitializationSettings IAdvancedMediaCaptureInitializationSettings;
#ifdef __cplusplus
interface IAdvancedMediaCaptureInitializationSettings;
#endif /* __cplusplus */
#endif

#ifndef __IAdvancedMediaCaptureSettings_FWD_DEFINED__
#define __IAdvancedMediaCaptureSettings_FWD_DEFINED__
typedef interface IAdvancedMediaCaptureSettings IAdvancedMediaCaptureSettings;
#ifdef __cplusplus
interface IAdvancedMediaCaptureSettings;
#endif /* __cplusplus */
#endif

#ifndef __IAdvancedMediaCapture_FWD_DEFINED__
#define __IAdvancedMediaCapture_FWD_DEFINED__
typedef interface IAdvancedMediaCapture IAdvancedMediaCapture;
#ifdef __cplusplus
interface IAdvancedMediaCapture;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <mfobjects.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <winapifamily.h>
#if NTDDI_VERSION >= NTDDI_WIN8
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
/*****************************************************************************
 * IAdvancedMediaCaptureInitializationSettings interface
 */
#ifndef __IAdvancedMediaCaptureInitializationSettings_INTERFACE_DEFINED__
#define __IAdvancedMediaCaptureInitializationSettings_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAdvancedMediaCaptureInitializationSettings, 0x3de21209, 0x8ba6, 0x4f2a, 0xa5,0x77, 0x28,0x19,0xb5,0x6f,0xf1,0x4d);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("3de21209-8ba6-4f2a-a577-2819b56ff14d")
IAdvancedMediaCaptureInitializationSettings : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE SetDirectxDeviceManager(
        IMFDXGIDeviceManager *pManager) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAdvancedMediaCaptureInitializationSettings, 0x3de21209, 0x8ba6, 0x4f2a, 0xa5,0x77, 0x28,0x19,0xb5,0x6f,0xf1,0x4d)
#endif
#else
typedef struct IAdvancedMediaCaptureInitializationSettingsVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAdvancedMediaCaptureInitializationSettings *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAdvancedMediaCaptureInitializationSettings *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAdvancedMediaCaptureInitializationSettings *This);

    /*** IAdvancedMediaCaptureInitializationSettings methods ***/
    HRESULT (STDMETHODCALLTYPE *SetDirectxDeviceManager)(
        IAdvancedMediaCaptureInitializationSettings *This,
        IMFDXGIDeviceManager *pManager);

    END_INTERFACE
} IAdvancedMediaCaptureInitializationSettingsVtbl;

interface IAdvancedMediaCaptureInitializationSettings {
    CONST_VTBL IAdvancedMediaCaptureInitializationSettingsVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAdvancedMediaCaptureInitializationSettings_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAdvancedMediaCaptureInitializationSettings_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAdvancedMediaCaptureInitializationSettings_Release(This) (This)->lpVtbl->Release(This)
/*** IAdvancedMediaCaptureInitializationSettings methods ***/
#define IAdvancedMediaCaptureInitializationSettings_SetDirectxDeviceManager(This,pManager) (This)->lpVtbl->SetDirectxDeviceManager(This,pManager)
#else
/*** IUnknown methods ***/
static inline HRESULT IAdvancedMediaCaptureInitializationSettings_QueryInterface(IAdvancedMediaCaptureInitializationSettings* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAdvancedMediaCaptureInitializationSettings_AddRef(IAdvancedMediaCaptureInitializationSettings* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAdvancedMediaCaptureInitializationSettings_Release(IAdvancedMediaCaptureInitializationSettings* This) {
    return This->lpVtbl->Release(This);
}
/*** IAdvancedMediaCaptureInitializationSettings methods ***/
static inline HRESULT IAdvancedMediaCaptureInitializationSettings_SetDirectxDeviceManager(IAdvancedMediaCaptureInitializationSettings* This,IMFDXGIDeviceManager *pManager) {
    return This->lpVtbl->SetDirectxDeviceManager(This,pManager);
}
#endif
#endif

#endif


#endif  /* __IAdvancedMediaCaptureInitializationSettings_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IAdvancedMediaCaptureSettings interface
 */
#ifndef __IAdvancedMediaCaptureSettings_INTERFACE_DEFINED__
#define __IAdvancedMediaCaptureSettings_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAdvancedMediaCaptureSettings, 0x24e0485f, 0xa33e, 0x4aa1, 0xb5,0x64, 0x60,0x19,0xb1,0xd1,0x4f,0x65);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("24e0485f-a33e-4aa1-b564-6019b1d14f65")
IAdvancedMediaCaptureSettings : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetDirectxDeviceManager(
        IMFDXGIDeviceManager **ppManager) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAdvancedMediaCaptureSettings, 0x24e0485f, 0xa33e, 0x4aa1, 0xb5,0x64, 0x60,0x19,0xb1,0xd1,0x4f,0x65)
#endif
#else
typedef struct IAdvancedMediaCaptureSettingsVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAdvancedMediaCaptureSettings *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAdvancedMediaCaptureSettings *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAdvancedMediaCaptureSettings *This);

    /*** IAdvancedMediaCaptureSettings methods ***/
    HRESULT (STDMETHODCALLTYPE *GetDirectxDeviceManager)(
        IAdvancedMediaCaptureSettings *This,
        IMFDXGIDeviceManager **ppManager);

    END_INTERFACE
} IAdvancedMediaCaptureSettingsVtbl;

interface IAdvancedMediaCaptureSettings {
    CONST_VTBL IAdvancedMediaCaptureSettingsVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAdvancedMediaCaptureSettings_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAdvancedMediaCaptureSettings_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAdvancedMediaCaptureSettings_Release(This) (This)->lpVtbl->Release(This)
/*** IAdvancedMediaCaptureSettings methods ***/
#define IAdvancedMediaCaptureSettings_GetDirectxDeviceManager(This,ppManager) (This)->lpVtbl->GetDirectxDeviceManager(This,ppManager)
#else
/*** IUnknown methods ***/
static inline HRESULT IAdvancedMediaCaptureSettings_QueryInterface(IAdvancedMediaCaptureSettings* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAdvancedMediaCaptureSettings_AddRef(IAdvancedMediaCaptureSettings* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAdvancedMediaCaptureSettings_Release(IAdvancedMediaCaptureSettings* This) {
    return This->lpVtbl->Release(This);
}
/*** IAdvancedMediaCaptureSettings methods ***/
static inline HRESULT IAdvancedMediaCaptureSettings_GetDirectxDeviceManager(IAdvancedMediaCaptureSettings* This,IMFDXGIDeviceManager **ppManager) {
    return This->lpVtbl->GetDirectxDeviceManager(This,ppManager);
}
#endif
#endif

#endif


#endif  /* __IAdvancedMediaCaptureSettings_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IAdvancedMediaCapture interface
 */
#ifndef __IAdvancedMediaCapture_INTERFACE_DEFINED__
#define __IAdvancedMediaCapture_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAdvancedMediaCapture, 0xd0751585, 0xd216, 0x4344, 0xb5,0xbf, 0x46,0x3b,0x68,0xf9,0x77,0xbb);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("d0751585-d216-4344-b5bf-463b68f977bb")
IAdvancedMediaCapture : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetAdvancedMediaCaptureSettings(
        IAdvancedMediaCaptureSettings **ppSettings) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAdvancedMediaCapture, 0xd0751585, 0xd216, 0x4344, 0xb5,0xbf, 0x46,0x3b,0x68,0xf9,0x77,0xbb)
#endif
#else
typedef struct IAdvancedMediaCaptureVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAdvancedMediaCapture *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAdvancedMediaCapture *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAdvancedMediaCapture *This);

    /*** IAdvancedMediaCapture methods ***/
    HRESULT (STDMETHODCALLTYPE *GetAdvancedMediaCaptureSettings)(
        IAdvancedMediaCapture *This,
        IAdvancedMediaCaptureSettings **ppSettings);

    END_INTERFACE
} IAdvancedMediaCaptureVtbl;

interface IAdvancedMediaCapture {
    CONST_VTBL IAdvancedMediaCaptureVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAdvancedMediaCapture_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAdvancedMediaCapture_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAdvancedMediaCapture_Release(This) (This)->lpVtbl->Release(This)
/*** IAdvancedMediaCapture methods ***/
#define IAdvancedMediaCapture_GetAdvancedMediaCaptureSettings(This,ppSettings) (This)->lpVtbl->GetAdvancedMediaCaptureSettings(This,ppSettings)
#else
/*** IUnknown methods ***/
static inline HRESULT IAdvancedMediaCapture_QueryInterface(IAdvancedMediaCapture* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAdvancedMediaCapture_AddRef(IAdvancedMediaCapture* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAdvancedMediaCapture_Release(IAdvancedMediaCapture* This) {
    return This->lpVtbl->Release(This);
}
/*** IAdvancedMediaCapture methods ***/
static inline HRESULT IAdvancedMediaCapture_GetAdvancedMediaCaptureSettings(IAdvancedMediaCapture* This,IAdvancedMediaCaptureSettings **ppSettings) {
    return This->lpVtbl->GetAdvancedMediaCaptureSettings(This,ppSettings);
}
#endif
#endif

#endif


#endif  /* __IAdvancedMediaCapture_INTERFACE_DEFINED__ */

#endif /* WINAPI_PARTITION_APP */
#endif /* NTDDI >= NTDDI_WIN8 */
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __mfmediacapture_h__ */
