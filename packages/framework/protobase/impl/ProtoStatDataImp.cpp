#include "ProtoStatDataImp.h"
#include "ProtoTime.h"
#include <stdlib.h>

ProtoStatDataImp::ProtoStatDataImp()
{

}

ProtoStatDataImp::~ProtoStatDataImp()
{
	m_mapSidKeyTime.clear();
}

void	ProtoStatDataImp::rebind(uint32_t sid, uint32_t asid)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(asid);
	if( it == m_mapSidKeyTime.end() )
		return;
	
	m_mapSidKeyTime[sid] = it->second;
	m_mapSidKeyTime.erase(asid);
}

void	ProtoStatDataImp::probeTime(uint32_t sid, uint32_t key)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
	{
		keytime_t	keytime;
		keytime[key] = ProtoTime::currentSystemTime();

		m_mapSidKeyTime[sid] = keytime;
	}
	else
	{
		it->second.insert(std::make_pair(key, ProtoTime::currentSystemTime()));
	}
}

uint32_t	ProtoStatDataImp::getTime(uint32_t sid, uint32_t key)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
		return 0;

	keytime_it_t keyit = it->second.find(key);
	if( keyit == it->second.end() )
		return 0;

	return keyit->second;
}

uint32_t	ProtoStatDataImp::getSpendTime(uint32_t sid, uint32_t key1, uint32_t key2)
{
	uint32_t time1 = getTime(sid, key1);
	uint32_t time2 = getTime(sid, key2);

	if( time1 == 0 || time2 == 0 )
		return 0;

	return std::abs(time2-time1);
}

uint32_t    ProtoStatDataImp::getSpendTimeUp2Now(uint32_t sid, uint32_t key)
{
    uint32_t time1 = getTime(sid, key);
    uint32_t now = ProtoTime::currentSystemTime();
    
    if(time1 == 0 || now == 0)
        return 0;

    return std::abs(now - time1);
}

void		ProtoStatDataImp::setInt(uint32_t sid, uint32_t type, uint32_t value)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
		return;

	it->second[type] = value;
}

uint32_t	ProtoStatDataImp::getInt(uint32_t sid, uint32_t type)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
		return 0;

	keytime_it_t keyit = it->second.find(type);
	if( keyit == it->second.end() )
		return 0;

	return keyit->second;
}

void		ProtoStatDataImp::setString(uint32_t sid, uint32_t type, std::string value)
{

}

std::string ProtoStatDataImp::getString(uint32_t sid, uint32_t type)
{
	return "";
}

bool	ProtoStatDataImp::has(uint32_t sid, uint32_t key)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
		return false;

	keytime_it_t keyit = it->second.find(key);
	if( keyit == it->second.end() )
		return false;

	return true;
}

void	ProtoStatDataImp::reset(uint32_t sid)
{
	sidkeytime_it_t it = m_mapSidKeyTime.find(sid);
	if( it == m_mapSidKeyTime.end() )
		return;

	it->second.clear();
}
