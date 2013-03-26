#include "ProtoLinkMgrImp.h"

ProtoLinkMgrImp::ProtoLinkMgrImp()
{

}

void	ProtoLinkMgrImp::add(uint32_t connId)
{
	m_setLinks.insert(connId);
}

void	ProtoLinkMgrImp::remove(uint32_t connId)
{
	m_setLinks.erase(connId);
}

bool	ProtoLinkMgrImp::hasLink(uint32_t connId)
{
	return m_setLinks.find(connId)!=m_setLinks.end();
}