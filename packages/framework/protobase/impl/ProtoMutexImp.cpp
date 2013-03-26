#include "ProtoMutexImp.h"

ProtoMutexImp::ProtoMutexImp()
{
#ifdef  _WIN32
    mMutex = ::CreateMutex(NULL, FALSE, NULL);
#else
    pthread_mutex_init(&mMutex, NULL);
#endif
}

ProtoMutexImp::~ProtoMutexImp()
{
#ifdef _WIN32
	::CloseHandle(mMutex);
#else
    pthread_mutex_destroy(&mMutex);
#endif
}


void	ProtoMutexImp::lock()
{
#ifdef _WIN32
	switch( ::WaitForSingleObject(mMutex, INFINITE) )
	{
	case WAIT_OBJECT_0:
		break;
	case WAIT_ABANDONED: 
		break; 
	}
#else
   pthread_mutex_lock(&mMutex);
#endif
}

void	ProtoMutexImp::unlock()
{
#ifdef _WIN32
	ReleaseMutex(mMutex);
#else
    pthread_mutex_unlock(&mMutex);
#endif
}

