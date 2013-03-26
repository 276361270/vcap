#ifndef PROTOWINTHREAD_H
#define PROTOWINTHREAD_H

#include "IProtoTaskThread.h"
//#include "dwutility/locker.h"
#include <atlbase.h>
#include <atlwin.h>
#include <vector>
#include <list>
#include <deque>

//#define WM_ON_PROTO_DATA (WM_USER + 0x9100)
//#define WM_ON_PROTO_TIMER (WM_USER + 0x9101)

class IProtoTask;
class ProtoMutex;
class ProtoWinThread 
	: public IProtoTaskThread
	, public CWindowImpl<ProtoWinThread>
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
	ProtoWinThread(void* context);
	virtual ~ProtoWinThread();

	BEGIN_MSG_MAP(ProtoWinThread)
		//MESSAGE_HANDLER(WM_ON_PROTO_DATA, OnData)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()

public:
	LRESULT OnTimer(UINT, WPARAM, LPARAM, BOOL&);
	void	onTasks();
	void	onDelayTasks();

	virtual void	post(IProtoTask* task);
	virtual void	post(IProtoTask* task, uint32_t delay);
	virtual void	remove(IProtoTask* task);
	virtual	void	stop();
	virtual	void	clear();

private:
	void*		m_pContext;
	ProtoMutex* mMutex;
	ProtoMutex*	mDelayMutex;

	std::vector<IProtoTask*>	mTasks;	
	std::deque<IProtoTask*>	mSavedTasks;

	uint32_t	m_nNext;
	std::vector<TaskContext>	mDelayTasks;
};

#endif
