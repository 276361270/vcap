#ifndef	PROTOMUTEX_H
#define PROTOMUTEX_H

#include "ProtoConfig.h"

class ProtoMutexImp;
class SESSCOMM_API ProtoMutex
{
public:
	ProtoMutex();
	~ProtoMutex();

public:
	void	lock();
	void	unlock();

private:
    ProtoMutexImp*  m_pMutexImp;
};



class SESSCOMM_API ProtoAutoLock
{
public:
    explicit ProtoAutoLock(ProtoMutex *m)
        : m_lock(m)
    {
        m_lock->lock();
    }

    ~ProtoAutoLock()
    {
        m_lock->unlock();
        m_lock = NULL;
    }

private:
    ProtoMutex* m_lock;
};

#define PROTO_AUTO_LOCK(x) ProtoAutoLock __auto_lock_yaphet__(x);

#endif
