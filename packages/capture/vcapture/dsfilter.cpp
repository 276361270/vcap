#include "dsfilter.h"
#include "dspin.h"

DSFilter::DSFilter(IBaseFilter* filter)
: m_pBaseFilter(filter)
{
	//enum pins:
	enumPins();
}

DSFilter::DSFilter(IMoniker* moniker)
{
	IPropertyBag *pPropBag;
	HRESULT	hr = ERROR_SUCCESS;
	hr = moniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
	if(SUCCEEDED(hr))
	{
		// To retrieve the filter's friendly name, do the following:
		VARIANT varName;
		VariantInit(&varName);
		hr = pPropBag->Read(L"FriendlyName", &varName, 0);
		if (SUCCEEDED(hr))
		{
			// Display the name in your UI somehow.
			m_wstrName.assign(varName.bstrVal);
		}
		VariantClear(&varName);
	}
	moniker->BindToObject(NULL, NULL, IID_IBaseFilter,(void**)&m_pBaseFilter);

	//enum pins:
	enumPins();
}

DSFilter::~DSFilter()
{

}

void	DSFilter::enumPins()
{
	if( !m_pBaseFilter )
		return;

	IEnumPins*	pEnumPings = NULL;
	m_pBaseFilter->EnumPins(&pEnumPings);
	IPin*		pPin;
	ULONG		fetched=0;
	HRESULT		hr = S_OK;
	while( true ) 
	{
		hr = pEnumPings->Next(1, &pPin, &fetched);
		if( FAILED(hr) || fetched ==0 || !pPin)
			break;

		m_arrPins.push_back( new DSPin(pPin) );
	}
}

DSPin*	DSFilter::getOutputPin()
{
	DSPin* pin = NULL;
	for( size_t i =0; i<m_arrPins.size(); i++ ) 
	{
		pin = m_arrPins[i];
		if( pin == NULL )
			continue;

		if( pin->isOutput() )
		{
			break;
		}
	}

	return pin;
}