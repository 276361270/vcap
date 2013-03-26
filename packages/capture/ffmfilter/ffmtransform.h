#ifndef FFMTRANSFORM_H
#define FFMTRANSFORM_H

#include "ffmfilter.h"

class FfmAacHandler;
class FfmH264Handler;
class FfmTransform
{
public:
	FfmTransform();
	~FfmTransform();

public:
	void	open();
	int		onData(int media_type, char* src, int inlen, char* dest, int outlen);
	void	close();

private:
	FfmAacHandler*	m_pAacHandler;
	FfmH264Handler* m_pH264Handler;
};

#endif