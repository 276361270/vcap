#include "mutex.h"

//static AdaptLock g_AdaptLock_CG; //为了能在CConnMgr::Instance里有一个已经初始化的锁，声明了一个静态全局变量
//static AdaptLock g_AdaptLock_IO; //for IoEngine to get Instance
//static AdaptLock g_AdaptLock_POOL; //for memory pool
AdaptLock* AdaptLock::m_pIns = NULL; //for m_connMap in ConnMgr and IoEngine(both 2 resources)


AdaptLock::AdaptLock()
{
// #ifdef WIN32
//     InitializeCriticalSection(&m_lock);
// #else
//     pthread_mutex_init(&m_lock, NULL);
// #endif
    m_pLock = new MutexLock();
}

AdaptLock::~AdaptLock()
{
//	DeleteCriticalSection(&m_lock);
    delete m_pLock;
}

// AdaptLock& AdaptLock::Ins_CG()
// {
//     return g_AdaptLock_CG;
// }
// 
// AdaptLock& AdaptLock::Ins_IO()
// {
//     return g_AdaptLock_IO;
// }
// 
// AdaptLock& AdaptLock::Ins_POOL()
// {
//     return g_AdaptLock_POOL;
// }

AdaptLock* AdaptLock::Instance()
{
    if ( !m_pIns )
    {
        m_pIns = new AdaptLock();
    }
    return m_pIns;
}

void AdaptLock::Release()
{
    if ( m_pIns )
    {
        delete m_pIns;
        m_pIns = NULL;
    }
}

void AdaptLock::lock()
{
// #ifdef WIN32
//     EnterCriticalSection(&m_lock);
// #else
//     pthread_mutex_lock(&m_lock);
// #endif
    m_pLock->lock();
}

void AdaptLock::unlock()
{
// #ifdef WIN32
//     LeaveCriticalSection(&m_lock);
// #else
//     pthread_mutex_unlock(&m_lock);
// #endif
    m_pLock->unlock();
}

//-----------------------------------
#ifdef WIN32
AutoLock::AutoLock(CRITICAL_SECTION& cs)
: m_lk(cs)
{
    EnterCriticalSection(&m_lk);
}
#else
AutoLock::AutoLock(pthread_mutex_t& mt)
: m_lk(mt)
{
    pthread_mutex_lock(&m_lk);
}
#endif

AutoLock::~AutoLock()
{
#ifdef WIN32
    LeaveCriticalSection(&m_lk);		
#else
    pthread_mutex_unlock(&m_lk);
#endif
}

//--------------------------------
MutexLock::MutexLock()
{
#ifdef WIN32	
    m_lk = ::CreateMutex(NULL, FALSE, NULL);
    //InitializeCriticalSection(&m_lk);
#else
    pthread_mutex_init(&m_lk, NULL);
#endif
}

MutexLock::~MutexLock()
{
#ifdef WIN32
    ::CloseHandle(m_lk);
    //DeleteCriticalSection(&m_lk);
#else
    pthread_mutex_destroy(&m_lk);
#endif
}

void MutexLock::lock()
{
#ifdef WIN32
    //EnterCriticalSection(&m_lk);

    switch( ::WaitForSingleObject(m_lk, INFINITE) )
    {
    case WAIT_OBJECT_0:
        break;
    case WAIT_ABANDONED: 
        break; 
    }
#else
    pthread_mutex_lock(&m_lk);
#endif
}

void MutexLock::unlock()
{
#ifdef WIN32
    //LeaveCriticalSection(&m_lk);
    ReleaseMutex(m_lk);
#else
    pthread_mutex_unlock(&m_lk);
#endif
}


