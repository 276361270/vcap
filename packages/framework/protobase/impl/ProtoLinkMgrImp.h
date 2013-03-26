#ifndef PROTOLINKMGRIMP_H
#define PROTOLINKMGRIMP_H

#include "ProtoConfig.h"
#include <set>

class ProtoLinkMgrImp;
class ProtoLinkMgrImp
{
public:
	ProtoLinkMgrImp();
	
public:
	void	add(uint32_t connId);
	void	remove(uint32_t connId);
	bool	hasLink(uint32_t connId);
	
private:
	std::set<uint32_t>	m_setLinks;
};

#endif
