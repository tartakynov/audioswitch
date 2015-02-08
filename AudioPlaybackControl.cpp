/* ***************************************************************************
 * Include Files
 * **************************************************************************/

#include "AudioPlaybackControl.h"
#include "IPolicyConfig.h"


/* ***************************************************************************
 * Constants
 * **************************************************************************/

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);

const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);


/* ***************************************************************************
 * Functions
 * **************************************************************************/

/* Sets default audio playback device to the one specified by ID. */
HRESULT SetDefaultAudioPlaybackDevice( LPCWSTR devID )
{
    IPolicyConfigVista *pPolicyConfig;
    HRESULT hr = CoCreateInstance(
        __uuidof(CPolicyConfigVistaClient),
        NULL, 
        CLSCTX_ALL, 
        __uuidof(IPolicyConfigVista), 
        (LPVOID *)&pPolicyConfig
    );

    if (SUCCEEDED(hr))
    {
        hr = pPolicyConfig->SetDefaultEndpoint(devID, eConsole);
        pPolicyConfig->Release();
    }

    return hr;
}


/* Enumerates all active (plugged in) audio rendering endpoint devices and 
 * switches default endpoint to the next from current. */
void NextAudioPlaybackDevice( void )
{
    HRESULT hr = S_OK;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDeviceCollection *pCollection = NULL;
    IMMDevice *pEndpoint = NULL;
    IMMDevice *pDefaultEndpoint = NULL;
    IMMDevice *pNextEndpoint = NULL;
    IPropertyStore *pProps = NULL;
    LPWSTR pwszID = NULL;
    LPWSTR pwszDefaultID = NULL;
    LPWSTR pwszNextID = NULL;
    ULONG next = 0;

    hr = CoInitialize(NULL);
    EXIT_ON_ERROR(hr)

    hr = CoCreateInstance(
        CLSID_MMDeviceEnumerator, 
        NULL,
        CLSCTX_ALL, 
        IID_IMMDeviceEnumerator,
        (void**)&pEnumerator
    );
    EXIT_ON_ERROR(hr)

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultEndpoint);
    EXIT_ON_ERROR(hr)

    hr = pDefaultEndpoint->GetId(&pwszDefaultID);
    EXIT_ON_ERROR(hr)

    hr = pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pCollection);
    EXIT_ON_ERROR(hr)

    UINT  count;
    hr = pCollection->GetCount(&count);
    EXIT_ON_ERROR(hr)
    
    for (ULONG i = 0; i < count; i++)
    {
        // Get pointer to endpoint number i.
        hr = pCollection->Item(i, &pEndpoint);
        EXIT_ON_ERROR(hr)

        // Get the endpoint ID string.
        hr = pEndpoint->GetId(&pwszID);
        EXIT_ON_ERROR(hr)
        
        if ( wcscmp( pwszDefaultID, pwszID ) == 0 ) 
        {
            next = (i + 1 < count) ? i + 1 : 0;
            hr = pCollection->Item(next, &pNextEndpoint);
            EXIT_ON_ERROR(hr)

            hr = pNextEndpoint->OpenPropertyStore(STGM_READ, &pProps);
            EXIT_ON_ERROR(hr)

            PROPVARIANT varName;
            PropVariantInit(&varName);

            // Get the endpoint's friendly-name property.
            hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
            EXIT_ON_ERROR(hr)

            // Get the endpoint ID string.
            hr = pNextEndpoint->GetId(&pwszNextID);
            EXIT_ON_ERROR(hr)
                        
            // Print endpoint friendly name and endpoint ID.
            #ifdef DEBUG
            printf("Endpoint %d: %S\n", next, varName.pwszVal);            
            #endif
            
            SetDefaultAudioPlaybackDevice(pwszNextID);
            
            CoTaskMemFree(pwszNextID);
            SAFE_RELEASE(pNextEndpoint)
            //PropVariantClear(&varName);
            //SAFE_RELEASE(pProps)
        }
               
        CoTaskMemFree(pwszID);
        pwszID = NULL;
        SAFE_RELEASE(pEndpoint)
    }

    CoTaskMemFree(pwszDefaultID);
    SAFE_RELEASE(pDefaultEndpoint)
    SAFE_RELEASE(pEnumerator)
    SAFE_RELEASE(pCollection)
    return;

Exit:
    CoTaskMemFree(pwszID);
    SAFE_RELEASE(pEnumerator)
    SAFE_RELEASE(pCollection)
    SAFE_RELEASE(pEndpoint)
    SAFE_RELEASE(pProps)
}

