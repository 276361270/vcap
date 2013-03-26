#include "ProtoMutex.h"
#include "impl/ProtoMutexImp.h"

ProtoMutex::ProtoMutex()
{
    m_pMutexImp = new ProtoMutexImp();
}

ProtoMutex::~ProtoMutex()
{
    delete m_pMutexImp;
}


void	ProtoMutex::lock()
{
    m_pMutexImp->lock();
}

void	ProtoMutex::unlock()
{
    m_pMutexImp->unlock();
}

