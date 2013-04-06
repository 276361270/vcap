#include "ffmbuffer.h"

FfmBuffer::FfmBuffer(int frame_size)
: m_nFrameSize(frame_size)
{
	m_leftItem.buffer = NULL;
	m_leftItem.len = 0;
}

FfmBuffer::~FfmBuffer()
{

}

void	FfmBuffer::push(char* src, int len)
{
	int last = (m_leftItem.len==0)?0:m_nFrameSize-m_leftItem.len;
	int num = (len-last)/m_nFrameSize;
	int remain = (len-last)%m_nFrameSize;
	char* tmp = src;

	//fill the last left item first:
	if( m_leftItem.len != 0 ) {
		memcpy(m_leftItem.buffer+m_leftItem.len, tmp, last);
		m_arrBuffers.push_back(m_leftItem);

		m_leftItem.buffer = NULL;
		m_leftItem.len = 0;
		tmp += last;
	}

	//fill items:
	for( int i=0; i<num; i++ ) {
		FfmBufItem item;
		item.buffer = new char[m_nFrameSize];
		item.len = m_nFrameSize;
		memcpy(item.buffer, tmp, m_nFrameSize);
		m_arrBuffers.push_back(item);

		tmp += m_nFrameSize;
	}

	//handle the left bytes:
	if( remain > 0 ) {
		m_leftItem.buffer = new char[m_nFrameSize];
		memcpy(m_leftItem.buffer, tmp, remain);
		m_leftItem.len = remain;
	}
}

char*	FfmBuffer::pop()
{
	if( m_arrBuffers.size() == 0 ) {
		return NULL;
	}


	FfmBufItem item = m_arrBuffers.front();
	m_arrBuffers.pop_front();
	return item.buffer;
}