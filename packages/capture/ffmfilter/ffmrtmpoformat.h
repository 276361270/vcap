#ifndef FFMRTMPOFORMAT_H
#define FFMRTMPOFORMAT_H

#include "ffmoutformat.h"

class FfmRtmpOFormat : public FfmOutFormat
{
public:
	FfmRtmpOFormat(char* ip, int port, char* app, char* stream);

};

#endif