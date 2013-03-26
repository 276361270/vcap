#ifndef IDSXFILTER_H
#define IDSXFILTER_H

#define STR_SPXFILTER	L"VCapSpxFilter"

// {6542F414-C8A4-4bfe-84FE-B0C059E8CBBB}
DEFINE_GUID(CLSID_SPXFILTER, 
0x6542f414, 0xc8a4, 0x4bfe, 0x84, 0xfe, 0xb0, 0xc0, 0x59, 0xe8, 0xcb, 0xbb);

// {57012E25-0187-4d62-8E7C-ACD05FECD503}
DEFINE_GUID(IID_SPXFILTER, 
0x57012e25, 0x187, 0x4d62, 0x8e, 0x7c, 0xac, 0xd0, 0x5f, 0xec, 0xd5, 0x3);



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