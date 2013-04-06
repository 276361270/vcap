#ifndef FFMBUFFER_H
#define FFMBUFFER_H

#include "ffmconfig.h"
#include <list>

struct FfmBufItem
{
	char*	buffer;
	int		len;
};

class FfmBuffer
{
public:
	FfmBuffer(int frame_size);
	~FfmBuffer();

public:
	void	push(char* src, int len);
	char*	pop();

private:
	int		m_nFrameSize;
	std::list<FfmBufItem>	m_arrBuffers;
	FfmBufItem	m_leftItem;
};

#endif