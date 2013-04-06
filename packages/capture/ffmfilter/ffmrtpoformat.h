#ifndef FFMRTPOFORMAT_H
#define FFMRTPOFORMAT_H

#include "ffmoutformat.h"

class FfmRtpOFormat : public FfmOutFormat
{
public:
	FfmRtpOFormat(char* ip, int port, char* app, char* stream);

};

#endif