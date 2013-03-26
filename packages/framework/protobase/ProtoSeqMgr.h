#ifndef PROTOSEQMGR_H
#define PROTOSEQMGR_H

#include "ProtoConfig.h"

class SESSCOMM_API ProtoSeqMgr
{
public:
	ProtoSeqMgr();
	ProtoSeqMgr(int max);

public:
	void	addSeq(uint32_t seq);
	bool	isDup(uint32_t seq);
	void	reset();

private:
	int		m_nMax;
	std::set<uint32_t>		m_arrSeqSet1;
	std::set<uint32_t>		m_arrSeqSet2;
	int		m_nIndex;
};


#endif