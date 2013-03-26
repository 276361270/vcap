#include "ProtoLgaData.h"

ProtoLgaData* ProtoLgaData::m_pInstance = NULL;

ProtoLgaData::ProtoLgaData()
: m_uWANIp(0)
, m_uCodeID(0)
, m_uLbsTime(0)
, m_uLinkdTime(0)
, m_uLoginTime(0)
, m_uUid(INVALID_UID)
, m_uProtoVer(0)
, m_bAnonymous(false)
, m_bSavePwd(false)
, m_bEmailLogin(false)
, m_ispType(CTL)
, m_testIsp(CTL)
, m_clientIsp(CTL)
, m_autoTestIsp(AUTO_DETECT)
, m_areaType(CTL_EAST)
{

} 

ProtoLgaData* ProtoLgaData::Instance()
{
    if ( !m_pInstance )
    {
        m_pInstance = new ProtoLgaData();
    }
    return m_pInstance;
}

