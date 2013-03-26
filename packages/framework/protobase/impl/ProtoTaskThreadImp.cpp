#include "ProtoTaskThreadImp.h"
#include "IProtoTask.h"
#include "ProtoMutex.h"
#include "ProtoUtils.h"
#include "ProtoTime.h"
#include "ProtoLog.h"
#include <stdio.h>

bool win_triggered_task(const ProtoTaskThreadImp::TaskContext& task)
{
	if( task.task == NULL )
		return true;

	return task.removed;
}

bool win_task_great(const ProtoTaskThreadImp::TaskContext& ct1, const ProtoTaskThreadImp::TaskContext& ct2)
{
	return (ct1.last + ct1.interval) < (ct2.last + ct2.interval);
}

bool operator==( const ProtoTaskThreadImp::TaskContext& ct1, const IProtoTask* task)
{
	return ct1.task == task;
}


#ifdef _WIN32
void __cdecl _TaskThread(void* pParam)     
#else
void* _TaskThread(void* pParam)
#endif
{
        if( pParam == NULL )
#ifdef _WIN32
                return;
#else
                return NULL;
#endif
        ProtoTaskThreadImp    *thread = (ProtoTaskThreadImp*)pParam;
        thread->run();
}

ProtoTaskThreadImp::ProtoTaskThreadImp(void* context) : mContext(context)
{	
    m_pMutex = new ProtoMutex();
    m_pDelayMutex = new ProtoMutex();

#ifdef _WIN32
	m_hThread = (HANDLE)_beginthread(_TaskThread, 0, this); 
	SetThreadPriority(m_hThread, THREAD_PRIORITY_ABOVE_NORMAL);
#else
        int ret = pthread_create(&m_hThread, NULL, &_TaskThread, this);
        if (ret != 0)
            //error
            std::cout << "ProtoTaskThreadImp::ProtoTaskThreadImp new thread failed!" << std::endl;
#endif
}

ProtoTaskThreadImp::~ProtoTaskThreadImp()
{
	PLOG("ProtoTaskThreadImp::~ProtoTaskThreadImp, enter.");
	stop();
	PLOG("ProtoTaskThreadImp::~ProtoTaskThreadImp, exit.");
}

//need optimize here:
void	ProtoTaskThreadImp::run()
{
	while( true )
	{	
		if( mDelayTasks.size() == 0 && mTasks.size() == 0 )
		{
			//take care here, no event is put here because I want this to be able to handle timer.
			//the timers need to be good for 100 millseconds.
                        //ProtoUtils::sleep(20); TO DO: will crash!!!
#ifdef WIN32
                    ::Sleep(20);
#else
                    ::usleep(100 * 1000); //100 ms
#endif
			continue;
		}

                onDelayTasks();
		onTasks();
                //ProtoUtils::sleep(20); TO DO: will crash!!!!
#ifdef WIN32
                ::Sleep(20);
#else
                ::usleep(100 * 1000); //100 ms
#endif
	}
}


void	ProtoTaskThreadImp::onTasks()
{
	uint32_t start = 0;
	uint32_t now = 0;
	IProtoTask* task = NULL;
	std::vector<IProtoTask*> tasks;
	if( mTasks.size() == 0 && mSaveTasks.size() == 0 )
		return;

	start = ProtoTime::currentSystemTime();

	m_pMutex->lock();
	if( mTasks.size() > 0 )
	{		
		mTasks.swap(tasks);
		mTasks.clear();
	}
	m_pMutex->unlock();

	for( size_t i=0; i<tasks.size(); i++ )
		mSaveTasks.push_back(tasks[i]);
	for( size_t i=0; i<mSaveTasks.size(); i++ )
	{
		task = mSaveTasks.front();
		if( !task )
			break;
		mSaveTasks.pop_front();

		task->run();
		delete task;

		now = ProtoTime::currentSystemTime();
		if( now - start >= 500 )
		{
			break;
		}
	}	
}

void	ProtoTaskThreadImp::onDelayTasks()
{
	uint32_t start = 0;

	//maybe I should put it after if.
	m_pDelayMutex->lock();
	if( mDelayTasks.size()> 0 )
	{
		start = ProtoTime::currentSystemTime();
		//for( std::vector<TaskContext>::iterator it=mDelayTasks.begin(); it !=mDelayTasks.end(); it++ )
		for( size_t i=0; i<mDelayTasks.size(); i++ )
		{
			TaskContext& tc = mDelayTasks[i];
			if( (start >tc.last + tc.interval) && (tc.task != NULL) && (!tc.removed) )
			{
				tc.task->run();

				//maybe removed during run:
				if( tc.task == NULL )
				{
					tc.removed = true;
					continue;
				}
				else if( tc.removed )
				{
					tc.task = NULL;
					continue;
				}

				if( tc.task && !tc.task->getRepeat() )
				{
					tc.removed = true;
				}
				else
				{
					//update the time:
					tc.last = ProtoTime::currentSystemTime();
				}
			}
		}
		//mDelayTasks.remove_if( win_triggered_task );
		//the only place to remove delay task.
		//we do this because in the run function, task may remove himself.
		//which will destory the iterator.
		mDelayTasks.erase(std::remove_if(mDelayTasks.begin(), mDelayTasks.end(), win_triggered_task), mDelayTasks.end());		
	}
	m_pDelayMutex->unlock();
}

void	ProtoTaskThreadImp::post(IProtoTask* task)
{
    m_pMutex->lock();
	mTasks.push_back(task);
    m_pMutex->unlock();
}

void	ProtoTaskThreadImp::post(IProtoTask* task, uint32_t delay)
{
	TaskContext tc;
	tc.task = task;
	tc.last = ProtoTime::currentSystemTime();
	tc.interval = delay;
	tc.removed = false;

	m_pDelayMutex->lock();	
	for( std::vector<TaskContext>::iterator it = mDelayTasks.begin(); it != mDelayTasks.end(); it++ )
	{
		if( it->task == task )
		{
			it->removed = true;
			it->task = NULL;
		}
	}
	mDelayTasks.push_back(tc);
	m_pDelayMutex->unlock();
}

void	ProtoTaskThreadImp::stop()
{
}

void	ProtoTaskThreadImp::remove(IProtoTask* task)
{
	if( !task )
		return;

	m_pMutex->lock();
	for( size_t i=0; i<mTasks.size(); i++ )
	{
		if( task == mTasks[i] )
		{
			delete mTasks[i];
		}				
	}
	mTasks.erase( std::remove(mTasks.begin(), mTasks.end(), task), mTasks.end() );

	for( size_t i=0; i<mSaveTasks.size(); i++ )
	{
		if( task == mSaveTasks[i] )
		{
			delete mSaveTasks[i];
		}				
	}
	mSaveTasks.erase( std::remove(mSaveTasks.begin(), mSaveTasks.end(), task), mSaveTasks.end() );
	m_pMutex->unlock();

	//delay tasks:
	m_pDelayMutex->lock();
	for( std::vector<TaskContext>::iterator it = mDelayTasks.begin(); it != mDelayTasks.end(); it++ )
	{
		if( it->task == task )
		{
			it->removed = true;
			it->task = NULL;
		}
	}
	m_pDelayMutex->unlock();
}

void	ProtoTaskThreadImp::clear()
{
	{
        m_pMutex->lock();
		for( size_t i=0; i<mTasks.size(); i++ )
		{
			delete mTasks[i];
		}
		mTasks.clear();

		for( size_t i=0; i<mSaveTasks.size(); i++ )
		{
			delete mSaveTasks[i];
		}
		mSaveTasks.clear();
        m_pMutex->unlock();
	}
	
	{
        m_pDelayMutex->lock();
		mDelayTasks.clear();
        m_pDelayMutex->unlock();
	}
}
