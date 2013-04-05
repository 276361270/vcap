#ifndef FFMTRANSFORM_H
#define FFMTRANSFORM_H

#include "ffmfilter.h"

class FfmOutFormat;
class FfmAacHandler;
class FfmH264Handler;
struct ICodecHandler;
class FfmTransform
{
public:
	FfmTransform();
	~FfmTransform();

public:
	int		setup(int media_type, char* ip, int port, char* app, char* stream);
	int		onData(LONGLONG time,  char* src, int inlen, char* dest, int outlen);
	void	close();
	void	setVideoSize(int width, int height);

private:
	ICodecHandler*	m_pCodecHandler;
	int		m_nMediaType;
};

#endif