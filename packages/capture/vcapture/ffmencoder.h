#ifndef FFMENCODER_H
#define FFMENCODER_H

#include "vcapconfig.h"

class DSFilter;
class FfmEncoder
{
public:
	FfmEncoder();
	~FfmEncoder();

public:	
	int			setup(int media_type, char* ip, int port, char* app, char* stream);
	DSFilter*	filter() { return m_pFilter; }

private:
	void		init();

private:
	DSFilter*		m_pFilter;
	IFfmFilter*		m_pFfmFilter;
	int				m_nMediaType;
};

#endif