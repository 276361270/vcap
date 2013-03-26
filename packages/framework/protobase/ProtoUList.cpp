#include "ProtoUList.h"
#include <algorithm>

ProtoUList::ProtoUList()
{
	m_bSorted = false;
}

ProtoUList::~ProtoUList()
{
	m_arrUids.clear();
}

void	ProtoUList::add(uint32_t uid)
{
	m_arrUids.push_back(uid);
}

void	ProtoUList::add(const std::vector<uint32_t>& uids)
{
	std::copy(uids.begin(), uids.end(), std::back_inserter(m_arrUids));
}

void	ProtoUList::add(const std::set<uint32_t>& uids)
{
	std::copy(uids.begin(), uids.end(), std::back_inserter(m_arrUids));
}

void	ProtoUList::remove(uint32_t uid)
{
	//m_arrUids.remove(uid);
	std::deque<uint32_t>::iterator it;
	for( it = m_arrUids.begin(); it != m_arrUids.end(); ++it )
	{
		if( *it == uid )
			break;
	}
	if( it != m_arrUids.end() )
		m_arrUids.erase(it);
}

void	ProtoUList::clear()
{
	m_arrUids.clear();
}

void	ProtoUList::sort()
{
	std::sort(m_arrUids.begin(), m_arrUids.end());
	m_bSorted = true;
}

uint32_t ProtoUList::size()
{
	return m_arrUids.size();
}

void	ProtoUList::fetch(std::vector<uint32_t>& uids, uint32_t size)
{
	uint32_t real_size = 0;

#ifdef _WIN32
    real_size = min(m_arrUids.size(), size);
#else
	real_size = std::min(m_arrUids.size(), size);
#endif

	uids.clear();

	if( real_size == 0 )
		return;

	uids.reserve(real_size);
	if( m_arrUids.size() == real_size )
	{
		uids.assign(m_arrUids.begin(), m_arrUids.end());
		m_arrUids.clear();
	}
	else
	{
		//the slower path
		for( uint32_t i=0; i<real_size; i++ )
		{
			uids.push_back( *m_arrUids.begin() );
			m_arrUids.pop_front();
		}	
	}
}

bool	ProtoUList::find(uint32_t uid)
{
	return (std::find(m_arrUids.begin(), m_arrUids.end(), uid) != m_arrUids.end());
}
