#include "ProtoSUMap.h"
#include "ProtoUList.h"
#include "ProtoLog.h"

ProtoSUMap::ProtoSUMap()
{

}

ProtoSUMap::~ProtoSUMap()
{
	m_arrUserMap.clear();
}

void	ProtoSUMap::add(uint32_t sid, uint32_t uid)
{
	sumap_type::iterator it = m_arrUserMap.find(sid);
	if( it == m_arrUserMap.end() )
	{
		suset_type ulist;
		ulist.insert(uid);

		m_arrUserMap[sid] = ulist;
	}
	else
	{
		it->second.insert(uid);
	}
}

void	ProtoSUMap::add(uint32_t sid, const std::vector<uint32_t>& uids)
{
	sumap_type::iterator it = m_arrUserMap.find(sid);
	if( it == m_arrUserMap.end() )
	{
		suset_type ulist;
		std::copy(uids.begin(), uids.end(), std::inserter(ulist, ulist.begin()));
		
		m_arrUserMap[sid] = ulist;
	}
	else
	{
		std::copy(uids.begin(), uids.end(), std::inserter(it->second, it->second.begin()));
	}
}

void	ProtoSUMap::add(uint32_t sid, const std::set<uint32_t>& uids)
{
	sumap_type::iterator it = m_arrUserMap.find(sid);
	if( it == m_arrUserMap.end() )
	{
		suset_type ulist;
		std::copy(uids.begin(), uids.end(), std::inserter(ulist, ulist.begin()));

		m_arrUserMap[sid] = ulist;
	}
	else
	{
		std::copy(uids.begin(), uids.end(), std::inserter(it->second, it->second.begin()));
	}
}

void	ProtoSUMap::add(const sumap_type& map)
{
	std::copy(map.begin(), map.end(), std::inserter(m_arrUserMap, m_arrUserMap.begin()));
}

void	ProtoSUMap::add(const std::map<uint32_t, std::vector<uint32_t> >& map)
{
	for( std::map<uint32_t, std::vector<uint32_t> >::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		add( it->first, it->second);
	}
}

void	ProtoSUMap::add(const std::map<uint32_t, uint32_t>& partners)
{
	//std::copy(partners.begin(), partners.end(), std::inserter(m_arrUserMap, m_arrUserMap.begin()));
	for( std::map<uint32_t, uint32_t>::const_iterator it = partners.begin(); it != partners.end(); ++it )
	{
		add( it->second, it->first);
	}
}

void	ProtoSUMap::remove(uint32_t sid, uint32_t uid)
{
	sumap_type::iterator it = m_arrUserMap.find(sid);
	if( it != m_arrUserMap.end() )
	{
		it->second.erase(uid);
	}
}

void	ProtoSUMap::clear()
{
	m_arrUserMap.clear();
}

bool	ProtoSUMap::find(uint32_t sid, uint32_t uid)
{
	sumap_type::iterator it = m_arrUserMap.find(sid);
	if( it != m_arrUserMap.end() )
	{
		return (it->second.find(uid) != it->second.end());
	}
	return false;
}

void	ProtoSUMap::fetch(uint32_t pid, std::vector<uint32_t>& uids, uint32_t max)
{
	sumap_type::iterator it = m_arrUserMap.find(pid);
	if( it != m_arrUserMap.end() )
	{
		if( (int)it->second.size() < max )
		{
			uids.assign( it->second.begin(), it->second.end() );
			it->second.clear();
			m_arrUserMap.erase(it->first);
		}
		else
		{
			//[TBD] here.
			suset_type::iterator it2 = it->second.begin();
			std::advance(it2, max);

			uids.assign(it->second.begin(), it2);
			it->second.erase(it->second.begin(), it2);
		}
	}

	while( (int)uids.size() < max )
	{
		it = m_arrUserMap.begin();
		if( it != m_arrUserMap.end() )
		{
			if( (int)(it->second.size() + uids.size()) < max )
			{
				std::copy(it->second.begin(), it->second.end(), std::back_inserter(uids));
				it->second.clear();
				m_arrUserMap.erase(it->first);
				continue;
			}
			else
			{
				//[TBD] here.
				suset_type::iterator it2 = it->second.begin();
				std::advance(it2, max-uids.size());

				//uids.assign(it->second.begin(), it2);
				std::copy(it->second.begin(), it2, std::back_inserter(uids));
				it->second.erase(it->second.begin(), it2);
				break;
			}
		}
		else
		{
			break;
		}
	}
}