#ifndef _NETMOD_MUTEX_LOCK_H_
#define _NETMOD_MUTEX_LOCK_H_
#include "protonet.h"

//actually it's a wrapper for multi-platforms
class MutexLock
{
public:
    MutexLock();
    ~MutexLock();

public:
    void lock();
    void unlock();

private:
#ifdef WIN32
    HANDLE m_lk;
    //CRITICAL_SECTION	m_lk;
#else
    pthread_mutex_t&  m_lk;
#endif
};

class AdaptLock
{
public:
    AdaptLock();
    ~AdaptLock();

public:
    void lock();
    void unlock();

    static AdaptLock* Instance();
    static void Release();
    //static AdaptLock& Ins_CG(); //for ConnMgr
    //static AdaptLock& Ins_IO(); //for IoEngine
    //static AdaptLock& Ins_POOL(); //for memory poor

private:
    static AdaptLock*   m_pIns;
    MutexLock*  m_pLock;
// #ifdef WIN32
//     CRITICAL_SECTION m_lock;
// #else
//     pthread_mutex_t  m_lock;
// #endif
};


//---------------------------------------------
class AutoLock
{
public:
#ifdef WIN32
    AutoLock(CRITICAL_SECTION& cs);
#else
    AutoLock(pthread_mutex_t& mt);
#endif
    ~AutoLock();

private:
#ifdef WIN32
    CRITICAL_SECTION& m_lk;
#else
    pthread_mutex_t&  m_lk;
#endif
};

//----------------------------------------

#endif


