#ifndef IPROTOTASKTHREAD_H
#define IPROTOTASKTHREAD_H

#include "ProtoConfig.h"

class IProtoTask;
class ProtoTaskThreadImp;
class SESSCOMM_API IProtoTaskThread
{
public:
	virtual ~IProtoTaskThread(){}
	virtual void	post(IProtoTask* task) = 0;
	virtual void	post(IProtoTask* task, uint32_t delay) = 0;
	virtual void	remove(IProtoTask* task) = 0;
	virtual	void	stop() = 0;
	virtual	void	clear() = 0;
};



#endif