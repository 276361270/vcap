#include "ProtoWinThread.h"
#include "ProtoMutex.h"
#include "ProtoLog.h"
#include "ProtoTime.h"
#include "IProtoTask.h"
#include <algorithm>

bool win_triggered_task(const ProtoWinThread::TaskContext& task)
{
	if( task.task == NULL )
		return true;
	
	return task.removed;
}

bool win_task_great(const ProtoWinThread::TaskContext& ct1, const ProtoWinThread::TaskContext& ct2)
{
	return (ct1.last + ct1.interval) < (ct2.last + ct2.interval);
}

bool operator==( const ProtoWinThread::TaskContext& ct1, const IProtoTask* task)
{
	return ct1.task == task;
}

ProtoWinThread::ProtoWinThread(void* context) : m_pContext(context)
{
	Create(HWND_MESSAGE, NULL, NULL, WS_POPUP);
	//SetTimer(WM_ON_PROTO_TIMER, 1000, NULL);
	::SetTimer(m_hWnd, 1, 100, NULL);
	::SetTimer(m_hWnd, 2, 100, NULL);
    mMutex = new ProtoMutex();
	mDelayMutex = new ProtoMutex();
}

ProtoWinThread::~ProtoWinThread()
{
	KillTimer(1);
	KillTimer(2);
	DestroyWindow();	

	clear();
}

LRESULT ProtoWinThread::OnTimer(UINT cmd, WPARAM w, LPARAM l, BOOL& b)
{
	if( w == 1 )
	{
		::SetTimer(m_hWnd, 1, 50, NULL);
		onDelayTasks();
	}
	else if( w == 2 )
	{
		::SetTimer(m_hWnd, 2, 50, NULL);
		onTasks();
	}	

	return 0;
}

void	ProtoWinThread::onTasks()
{
	uint32_t start = 0;
	uint32_t now = 0;
	IProtoTask* task = NULL;
	std::vector<IProtoTask*> tasks;
	if( mTasks.size() == 0 && mSavedTasks.size() == 0 )
		return;

	start = ProtoTime::currentSystemTime();

	{
		mMutex->lock();
		if( mTasks.size() > 0 )
		{		
			mTasks.swap(tasks);
			mTasks.clear();
		}
        mMutex->unlock();
	}
	
	for( size_t i=0; i<tasks.size(); i++ )
		mSavedTasks.push_back(tasks[i]);
	for( size_t i=0; i<mSavedTasks.size(); i++ )
	{
		task = mSavedTasks.front();
		if( !task )
			break;
		mSavedTasks.pop_front();

		task->run();
		delete task;

		now = ProtoTime::currentSystemTime();
		if( now - start >= 1000 )
		{
			break;
		}
	}	
}

void	ProtoWinThread::onDelayTasks()
{
	uint32_t start = 0;

	//maybe I should put it after if.
	mDelayMutex->lock();
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
    mDelayMutex->unlock();
}

void	ProtoWinThread::post(IProtoTask* task)
{
	//DW_AUTO_LOCKER(&mMutex);
    mMutex->lock();
	mTasks.push_back(task);
    mMutex->unlock();
	
	//PostMessage(WM_ON_PROTO_DATA,0, 0);
}

void	ProtoWinThread::post(IProtoTask* task, uint32_t delay)
{
	TaskContext tc;
	tc.task = task;
	tc.last = ProtoTime::currentSystemTime();
	tc.interval = delay;
	tc.removed = false;

	mDelayMutex->lock();
	//mDelayTasks.erase( std::remove(mDelayTasks.begin(), mDelayTasks.end(), task), mDelayTasks.end() );
	for( std::vector<TaskContext>::iterator it = mDelayTasks.begin(); it != mDelayTasks.end(); it++ )
	{
		if( it->task == task )
		{
			it->removed = true;
			it->task = NULL;
		}
	}
	mDelayTasks.push_back(tc);
    mDelayMutex->unlock();

	//std::sort(mDelayTasks.begin(), mDelayTasks.end(), win_task_great);
}

void	ProtoWinThread::remove(IProtoTask* task)
{
	if( !task )
		return;
	{
		mMutex->lock();
		for( size_t i=0; i<mTasks.size(); i++ )
		{
			if( task == mTasks[i] )
			{
				delete mTasks[i];
			}				
		}
		mTasks.erase( std::remove(mTasks.begin(), mTasks.end(), task), mTasks.end() );

		for( size_t i=0; i<mSavedTasks.size(); i++ )
		{
			if( task == mSavedTasks[i] )
			{
				delete mSavedTasks[i];
			}				
		}
		mSavedTasks.erase( std::remove(mSavedTasks.begin(), mSavedTasks.end(), task), mSavedTasks.end() );
        mMutex->unlock();
	}

	{
		mDelayMutex->lock();
		for( std::vector<TaskContext>::iterator it = mDelayTasks.begin(); it != mDelayTasks.end(); it++ )
		{
			if( it->task == task )
			{
				it->removed = true;
				it->task = NULL;
			}
		}
		//mDelayTasks.erase( std::remove(mDelayTasks.begin(), mDelayTasks.end(), task), mDelayTasks.end() );
        mDelayMutex->unlock();
	}
}

void	ProtoWinThread::stop()
{

}

void	ProtoWinThread::clear()
{
	{
		mMutex->lock();
		for( size_t i=0; i<mTasks.size(); i++ )
			delete mTasks[i];
		mTasks.clear();

		for( size_t i=0; i<mSavedTasks.size(); i++ )
			delete mSavedTasks[i];
		mSavedTasks.clear();
        mMutex->unlock();
	}
	
	{
		mDelayMutex->lock();
		//mDelayTasks.clear();
		for( std::vector<TaskContext>::iterator it = mDelayTasks.begin(); it != mDelayTasks.end(); it++ )
		{
			it->removed = true;
			it->task = NULL;
		}
        mDelayMutex->unlock();
	}
}