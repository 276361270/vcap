#include "spxconfig.h"
#include "spxfilter.h"

const AMOVIESETUP_MEDIATYPE sudPinTypes =
{
    &MEDIATYPE_NULL,       // Major type
    &MEDIASUBTYPE_NULL      // Minor type
};

const AMOVIESETUP_PIN sudpPins[] =
{
    { L"Input",             // Pins string name
      FALSE,                // Is it rendered
      FALSE,                // Is it an output
      FALSE,                // Are we allowed none
      FALSE,                // And allowed many
      &CLSID_NULL,          // Connects to filter
      NULL,                 // Connects to pin
      1,                    // Number of types
      &sudPinTypes          // Pin information
    },
    { L"Output",            // Pins string name
      FALSE,                // Is it rendered
      TRUE,                 // Is it an output
      FALSE,                // Are we allowed none
      FALSE,                // And allowed many
      &CLSID_NULL,          // Connects to filter
      NULL,                 // Connects to pin
      1,                    // Number of types
      &sudPinTypes          // Pin information
    }
};

const AMOVIESETUP_FILTER sudDsxFilter =
{
    &CLSID_SPXFILTER,         // Filter CLSID
    STR_SPXFILTER,       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    2,                      // Number of pins
    sudpPins                // Pin information
};


CFactoryTemplate g_Templates[]= {
    STR_SPXFILTER, &CLSID_SPXFILTER, SpxFilter::CreateInstance, NULL, &sudDsxFilter
};
int g_cTemplates = 1;   


STDAPI DllRegisterServer()   
{   
    return AMovieDllRegisterServer2 (TRUE);   
}   
  
STDAPI DllUnregisterServer()   
{   
    return AMovieDllRegisterServer2 (FALSE);   
}   
   

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);   
   
BOOL APIENTRY DllMain( HANDLE hModule,    
                       DWORD  ul_reason_for_call,    
                       LPVOID lpReserved   
                     )   
{   
    return DllEntryPoint((HINSTANCE)hModule,ul_reason_for_call,lpReserved);   
} 