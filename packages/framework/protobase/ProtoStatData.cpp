#include "ProtoStatData.h"
#include "impl/ProtoStatDataImp.h"

ProtoStatData*	ProtoStatData::s_pStatData = NULL;

ProtoStatData*	ProtoStatData::getInstance()
{
	if( !s_pStatData )
		s_pStatData = new ProtoStatData();

	return s_pStatData;
}

void	ProtoStatData::release()
{
	if( s_pStatData )
	{
		delete s_pStatData;
		s_pStatData = NULL;
	}
}

ProtoStatData::ProtoStatData()
{
	m_pStatImp = new ProtoStatDataImp();
}

ProtoStatData::~ProtoStatData()
{
	if( m_pStatImp )
		delete m_pStatImp;
}

void	ProtoStatData::rebind(uint32_t sid, uint32_t asid)
{
	m_pStatImp->rebind(sid, asid);
}

void	ProtoStatData::probeTime(uint32_t sid, uint32_t key)
{	
	m_pStatImp->probeTime(sid, key);
}

uint32_t	ProtoStatData::getTime(uint32_t sid, uint32_t key)
{
	return m_pStatImp->getTime(sid, key);
}

uint32_t	ProtoStatData::getSpendTime(uint32_t sid, uint32_t key1, uint32_t key2)
{
	return m_pStatImp->getSpendTime(sid, key1, key2);
}

uint32_t    ProtoStatData::getSpendTimeUp2Now(uint32_t sid, uint32_t key)
{
    return m_pStatImp->getSpendTimeUp2Now(sid, key);
}

void		ProtoStatData::setInt(uint32_t sid, uint32_t type, uint32_t value)
{
	m_pStatImp->setInt(sid, type, value);
}

uint32_t	ProtoStatData::getInt(uint32_t sid, uint32_t type)
{
	return m_pStatImp->getInt(sid, type);
}

void		ProtoStatData::setString(uint32_t sid, uint32_t type, std::string value)
{
	m_pStatImp->setString(sid, type, value);
}

std::string ProtoStatData::getString(uint32_t sid, uint32_t type)
{
	return m_pStatImp->getString(sid, type);
}

bool	ProtoStatData::has(uint32_t sid, uint32_t key)
{
	return m_pStatImp->has(sid, key);
}

void	ProtoStatData::reset(uint32_t sid)
{
	return m_pStatImp->reset(sid);
}