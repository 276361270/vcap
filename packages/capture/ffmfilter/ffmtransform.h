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
	void	open(int media_type);
	int		onData(int media_type, LONGLONG time,  char* src, int inlen, char* dest, int outlen);
	void	close();
	void	setVideoSize(int width, int height);

private:
	FfmAacHandler*	m_pAacHandler;
	FfmH264Handler* m_pH264Handler;
};

#endif