#include "ProtoSeqMgr.h"

ProtoSeqMgr::ProtoSeqMgr()
{
	m_nMax = 100;
	m_nIndex = 1;
}

ProtoSeqMgr::ProtoSeqMgr(int max)
{
	m_nMax = max;
}

void	ProtoSeqMgr::addSeq(uint32_t seq)
{
	if( m_nIndex == 1 )
	{
		if( m_arrSeqSet1.size() == m_nMax )
		{
			m_arrSeqSet2.clear();
			m_arrSeqSet2.insert(seq);
			m_nIndex = 2;
		}	
		else
		{
			m_arrSeqSet1.insert(seq);
		}
	}
	else if( m_nIndex == 2 )
	{
		if( m_arrSeqSet2.size() == m_nMax )
		{
			m_arrSeqSet1.clear();
			m_arrSeqSet1.insert(seq);
			m_nIndex = 1;
		}	
		else
		{
			m_arrSeqSet2.insert(seq);
		}
	}
}

bool	ProtoSeqMgr::isDup(uint32_t seq)
{
	return (m_arrSeqSet1.find(seq) != m_arrSeqSet1.end() ||
		m_arrSeqSet2.find(seq) != m_arrSeqSet2.end()
		);
}

void	ProtoSeqMgr::reset()
{
	m_nIndex = 1;
	m_arrSeqSet1.clear();
	m_arrSeqSet2.clear();
}