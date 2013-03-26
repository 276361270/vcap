#include "ProtoLinkMgr.h"
#include "impl/ProtoLinkMgrImp.h"

ProtoLinkMgr*	ProtoLinkMgr::s_pLinkMgr = NULL;
ProtoLinkMgr*	ProtoLinkMgr::getInstance()
{
	if( !s_pLinkMgr )
	{
		s_pLinkMgr = new ProtoLinkMgr();
	}
	return s_pLinkMgr;
}

void	ProtoLinkMgr::release()
{
	if( s_pLinkMgr )
	{
		delete s_pLinkMgr;
		s_pLinkMgr = NULL;
	}
}

ProtoLinkMgr::ProtoLinkMgr()
{
	m_pLinkMgrImp = new ProtoLinkMgrImp();
}

ProtoLinkMgr::~ProtoLinkMgr()
{
	delete m_pLinkMgrImp;
}

void	ProtoLinkMgr::add(uint32_t connId)
{
	m_pLinkMgrImp->add(connId);
}

void	ProtoLinkMgr::remove(uint32_t connId)
{
	m_pLinkMgrImp->remove(connId);
}

bool	ProtoLinkMgr::hasLink(uint32_t connId)
{
	return m_pLinkMgrImp->hasLink(connId);
}