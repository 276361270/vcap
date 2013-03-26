#ifndef	PROTOMUTEXIMP_H
#define PROTOMUTEXIMP_H

#include "ProtoConfig.h"

class ProtoMutexImp
{
public:
    ProtoMutexImp();
    ~ProtoMutexImp();

public:
	void	lock();
	void	unlock();

private:
#ifdef  _WIN32
	HANDLE	mMutex;
#else
    pthread_mutex_t mMutex;
#endif
};

#endif
