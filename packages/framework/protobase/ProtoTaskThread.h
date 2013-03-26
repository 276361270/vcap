#ifndef PROTOTASKTHREAD_H
#define PROTOTASKTHREAD_H

#include "ProtoConfig.h"
#include "IProtoTaskThread.h"

class IProtoTask;
//class ProtoTaskThreadImp;
class ProtoWinThread;
class SESSCOMM_API ProtoTaskThread : public IProtoTaskThread
{
public:
	ProtoTaskThread(void* context, bool background);
	~ProtoTaskThread();

public:
	void	run();
	void	post(IProtoTask* task);
	void	post(IProtoTask* task, uint32_t delay);
	void	stop();
	void	remove(IProtoTask* task);
	void	clear();

private:	
	IProtoTaskThread*	m_pThreadImp;
};



#endif
