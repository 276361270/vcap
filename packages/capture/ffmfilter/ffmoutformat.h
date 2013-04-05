#ifndef FFMOUTFORMAT_H
#define FFMOUTFORMAT_H

#include "ffmconfig.h"
#include <string>

class FfmOutFormat
{
public:
	FfmOutFormat();
	~FfmOutFormat();

public:
	void	init(char* fmt, char* url);
	void	connectServer();
	void	close();
	AVFormatContext*	getFormatContext() { return m_pFormatContext; }

private:
	AVFormatContext*	m_pFormatContext;
	std::string			m_strFmt;
	std::string			m_strUrl;
	bool				m_bOpened;
	bool				m_bConnected;
};

#endif