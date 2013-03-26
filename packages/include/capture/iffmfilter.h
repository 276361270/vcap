#ifndef IFFMFILTER_H
#define IFFMFILTER_H

#define STR_FFMFILTER	L"FfmFilter"

// {05367D36-7BFD-43a1-AF52-6C914BE7FCCF}
DEFINE_GUID(CLSID_FFMFILTER, 
0x5367d36, 0x7bfd, 0x43a1, 0xaf, 0x52, 0x6c, 0x91, 0x4b, 0xe7, 0xfc, 0xcf);

// {1CB68A0E-23CC-4701-8B38-80065C50C12F}
DEFINE_GUID(IID_FFMFILTER,
0x1cb68a0e, 0x23cc, 0x4701, 0x8b, 0x38, 0x80, 0x6, 0x5c, 0x50, 0xc1, 0x2f);

#define FFM_MEDIA_AUDIO		0
#define FFM_MEDIA_VIDEO		1

struct IFfmFilter
{
	virtual void	setMediaType(int type) = 0;
};

#endif