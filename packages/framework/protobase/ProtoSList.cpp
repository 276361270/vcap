#include "ProtoSList.h"
#include <algorithm>

ProtoSList::ProtoSList()
{
	m_bSorted = false;
}

void	ProtoSList::add(uint32_t uid)
{
	m_arrSids.push_back(uid);
}

void	ProtoSList::add(const std::vector<uint32_t>& uids)
{
	std::copy(uids.begin(), uids.end(), std::back_inserter(m_arrSids));
}

void	ProtoSList::add(const std::set<uint32_t>& uids)
{
	std::copy(uids.begin(), uids.end(), std::back_inserter(m_arrSids));
}

void	ProtoSList::remove(uint32_t uid)
{
	//m_arrUids.remove(uid);
	std::deque<uint32_t>::iterator it;
	for( it = m_arrSids.begin(); it != m_arrSids.end(); ++it )
	{
		if( *it == uid )
			break;
	}
	if( it != m_arrSids.end() )
		m_arrSids.erase(it);
}

void	ProtoSList::clear()
{
	m_arrSids.clear();
}

void	ProtoSList::sort()
{
	std::sort(m_arrSids.begin(), m_arrSids.end());
	m_bSorted = true;
}

uint32_t ProtoSList::size()
{
	return m_arrSids.size();
}

bool	ProtoSList::find(uint32_t uid)
{
	return (std::find(m_arrSids.begin(), m_arrSids.end(), uid) != m_arrSids.end());
}
