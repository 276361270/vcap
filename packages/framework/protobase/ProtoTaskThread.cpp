#include "ProtoTaskThread.h"
#include "impl/ProtoTaskThreadImp.h"
#include "impl/ProtoWinThread.h"


ProtoTaskThread::ProtoTaskThread(void* context, bool background)
{	
	if( !background )
		m_pThreadImp = new ProtoWinThread(context);
	else
		m_pThreadImp = new ProtoTaskThreadImp(context);
}

ProtoTaskThread::~ProtoTaskThread()
{
	if( m_pThreadImp )
		delete m_pThreadImp;
}

//need optimize here:
void	ProtoTaskThread::run()
{
	//m_pThreadImp->run();
}


void	ProtoTaskThread::post(IProtoTask* task)
{
	m_pThreadImp->post(task);
}

void	ProtoTaskThread::post(IProtoTask* task, uint32_t delay)
{
	m_pThreadImp->post(task, delay);
}

void	ProtoTaskThread::stop()
{
	m_pThreadImp->stop();
}

void	ProtoTaskThread::remove(IProtoTask* task)
{
	m_pThreadImp->remove(task);
}

void	ProtoTaskThread::clear()
{
	m_pThreadImp->clear();
}
