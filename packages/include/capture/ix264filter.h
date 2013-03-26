#ifndef IDSXFILTER_H
#define IDSXFILTER_H

#define STR_X264FILTER	L"VCapX264Filter"

DEFINE_GUID(CLSID_X264FILTER, 
0xf2e53bb2, 0x47e1, 0x4aad, 0x85, 0xe9, 0xff, 0xb9, 0xd9, 0x23, 0x71, 0x73);

// {2F1F1620-E3E4-44a6-90F2-9A9485F017BC}
DEFINE_GUID(IID_X264FILTER, 
0x2f1f1620, 0xe3e4, 0x44a6, 0x90, 0xf2, 0x9a, 0x94, 0x85, 0xf0, 0x17, 0xbc);

/*
struct IDsxCallback;
struct IDsxFilter
{
public:
	virtual void	setCallback(IDsxCallback* callback) = 0;
};

struct IDsxCallback
{
public:
	virtual void	onData(IMediaSample* src, IMediaSample* dest) = 0;
};
*/

#endif