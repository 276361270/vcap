#include "ProtoUSMap.h"

ProtoUSMap::ProtoUSMap()
{

}

ProtoUSMap::~ProtoUSMap()
{
	m_mapUMap.clear();
}

void	ProtoUSMap::add(uint32_t uid, uint32_t pid)
{
	m_mapUMap[uid] = pid;
}

void	ProtoUSMap::add(const std::map<uint32_t, uint32_t>& uids)
{
	std::copy(uids.begin(), uids.end(), std::inserter(m_mapUMap, m_mapUMap.begin()));
}

void	ProtoUSMap::remove(uint32_t uid)
{
	m_mapUMap.erase(uid);
}

void	ProtoUSMap::change(uint32_t uid, uint32_t pid)
{
	m_mapUMap[uid] = pid;
}

uint32_t	ProtoUSMap::getPid(uint32_t uid)
{
	umap_type::iterator it = m_mapUMap.find(uid);
	if( it == m_mapUMap.end() )
		return 0;

	return it->second;
}

uint32_t	ProtoUSMap::size()
{
	 return m_mapUMap.size();
}

ProtoUSMap::umap_type&	ProtoUSMap::getMap()
{
	return m_mapUMap;
}

void	ProtoUSMap::clear()
{
	m_mapUMap.clear();
}

uint32_t   ProtoUSMap::fetch(std::vector<uint32_t> &uids, uint32_t max)
{
    umap_type::iterator it = m_mapUMap.begin();
    uint32_t i = 0;

    uint32_t revSize = m_mapUMap.size() < max ? m_mapUMap.size() : max;
    if (revSize != 0)
    {
        uids.reserve(revSize);
    }

    while(it != m_mapUMap.end() && i < max)
    {
        uids.push_back(it->first);
        m_mapUMap.erase(it);
        i++;
    }

    return i;
}
