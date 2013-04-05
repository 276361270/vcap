#ifndef FFMTRANSFORM_H
#define FFMTRANSFORM_H

#include "ffmfilter.h"

class FfmOutFormat;
class FfmAacHandler;
class FfmH264Handler;
class FfmTransform
{
public:
	FfmTransform();
	~FfmTransform();

public:
	void	setup(int media_type, char* ip, int port, char* app, char* stream);
	int		onData(int media_type, LONGLONG time,  char* src, int inlen, char* dest, int outlen);
	void	close();
	void	setVideoSize(int width, int height);

private:
	FfmAacHandler*	m_pAacHandler;
	FfmH264Handler* m_pH264Handler;
};

#endif