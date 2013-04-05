#ifndef ICODECHANDLER_H
#define ICODECHANDLER_H

struct ICodecHandler
{
public:
	virtual int		setup(char* ip, int port, char* fmt, char* stream) = 0;
	virtual int		onData(LONGLONG time, char* src, int inlen, char* dest, int outlen) = 0;
	virtual void	close() = 0;
};

#endif