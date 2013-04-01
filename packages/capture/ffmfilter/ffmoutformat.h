#ifndef FFMOUTFORMAT_H
#define FFMOUTFORMAT_H

#include "ffmconfig.h"
#include <string>

class FfmOutFormat
{
public:
	FfmOutFormat(char* ip, short port);
	~FfmOutFormat();

public:
	void	open();
	void	close();
	AVFormatContext*	getFormatContext() { return m_pFormatContext; }

private:
	AVFormatContext*	m_pFormatContext;
	char*				m_pstrUrl;
};

#endif