#ifndef PROTOTASKTHREADIMP_H
#define PROTOTASKTHREADIMP_H

#include "ProtoConfig.h"
#include "IProtoTaskThread.h"
#include <list>
#include <vector>
#include <deque>

class IProtoTask;
class ProtoMutex;
//
// only delay_task can be set with repeat flag.
// repeat and delay_task will be deleted by owner.
// other task will be removed by ProtoTaskThreadImp.
//
class ProtoTaskThreadImp : public IProtoTaskThread
{
public:
	struct TaskContext
	{
		IProtoTask*	task;
		uint32_t	last;
		uint32_t	interval;
		bool		removed;
	};

public:
	ProtoTaskThreadImp(void* context);
	~ProtoTaskThreadImp();

public:
	void	run();
	void	onTasks();
	void	onDelayTasks();

	void	post(IProtoTask* task);
	void	post(IProtoTask* task, uint32_t delay);
	void	stop();
	void	remove(IProtoTask* task);
	void	clear();

private:	
	void*			mContext;
    ProtoMutex*     m_pMutex;
    ProtoMutex*     m_pDelayMutex;

#ifdef _WIN32
	HANDLE			m_hThread;
#else
    pthread_t               m_hThread;
#endif

	std::vector<IProtoTask*>	mTasks;	
	std::deque<IProtoTask*>		mSaveTasks;

	std::vector<TaskContext>	mDelayTasks;
};



#endif
