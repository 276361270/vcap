#ifndef PROTOLINKMGR_H
#define PROTOLINKMGR_H

#include "ProtoConfig.h"

class ProtoLinkMgrImp;
class SESSCOMM_API ProtoLinkMgr
{
public:
	static ProtoLinkMgr*	getInstance();
	static void		release();

private:
	ProtoLinkMgr();
	~ProtoLinkMgr();
	ProtoLinkMgr(const ProtoLinkMgr& other){};

public:
	void	add(uint32_t connId);
	void	remove(uint32_t connId);
	bool	hasLink(uint32_t connId);
	
private:
	ProtoLinkMgrImp*	m_pLinkMgrImp;
	static ProtoLinkMgr*s_pLinkMgr;
};

#endif
