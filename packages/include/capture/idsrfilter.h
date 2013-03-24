#ifndef IDSRFILTER
#define IDSRFILTER

DEFINE_GUID(CLSID_DSRFILTER, 
0x5842f480, 0x11fb, 0x454b, 0x8c, 0xf4, 0x65, 0x46, 0x48, 0xf1, 0xe1, 0x33);

DEFINE_GUID(IID_DSRFILTER, 
0x10ac035c, 0x52a3, 0x4d78, 0x9b, 0x8d, 0xe3, 0xab, 0xb2, 0x89, 0x94, 0x1e);


struct IDsrCallback;
struct IDsrFilter
{
public:
	virtual void	setCallback(IDsrCallback* callback) = 0;
};

struct IDsrCallback
{
public:
	virtual void	onData(void* data, int len) = 0;
};

#endif