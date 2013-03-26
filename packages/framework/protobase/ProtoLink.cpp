#include "ProtoLink.h"
#include "ProtoLinkMgr.h"

/*
#ifdef  _WIN32
#include "impl/ProtoLinkImp.h" 
using namespace core;
using namespace core::NetIO;
#else
#include "impl/ProtoUnixLinkImp.h"
#endif
*/
#include "impl/ProtoUnixLinkImp.h"

ProtoLink::ProtoLink(LinkType ltype, int encKey, IProtoLinkHandler* handler)
{
/*
#ifdef  _WIN32
	m_pLinkImp = new ProtoLinkImp(ltype, encKey, handler);
#else
    m_pLinkImp = new ProtoUnixLinkImp(ltype, encKey, handler);
#endif
*/
	m_pLinkImp = new ProtoUnixLinkImp(ltype, encKey, handler);
}

ProtoLink::~ProtoLink()
{
    if( m_pLinkImp )
        delete m_pLinkImp;
}

void ProtoLink::setProxy(protocol::IProxy* proxy)
{
	m_pLinkImp->setProxy(proxy);
}

bool ProtoLink::connect(uint32_t ip, const std::vector<uint16_t>& ports)
{
	bool ret = m_pLinkImp->connect(ip, ports);
	uint32_t connId = m_pLinkImp->getConnId();
	if( ret && connId != CONNID_INVALID )
	{
		ProtoLinkMgr::getInstance()->add(connId);
	}

	return ret;
}

bool ProtoLink::connect(std::string server, const std::vector<uint16_t>& ports)
{
	bool ret = m_pLinkImp->connect(server, ports);
	uint32_t connId = m_pLinkImp->getConnId();
	if( ret && connId != CONNID_INVALID )
	{
		ProtoLinkMgr::getInstance()->add(connId);
	}

	return ret;
}

bool	ProtoLink::reconnect()
{
	return m_pLinkImp->reconnect();
}

void ProtoLink::send(IProtoPacket* proto)
{	
	m_pLinkImp->send(proto);
}

void ProtoLink::send(const char* data, uint32_t len)
{	
	m_pLinkImp->send(data, len);
}

void ProtoLink::send(uint32_t uri, sox::Marshallable& req)
{
	m_pLinkImp->send(uri, req);
}

void ProtoLink::close()
{
	uint32_t connId = m_pLinkImp->getConnId();
	if( connId != CONNID_INVALID )
	{
		ProtoLinkMgr::getInstance()->remove(connId);
	}
	m_pLinkImp->close();
}

void		ProtoLink::setStatus(IProtoLink::LinkStatus status)
{
	m_pLinkImp->setStatus(status);
}

IProtoLink::LinkStatus	ProtoLink::getStatus()
{
	return (LinkStatus)m_pLinkImp->getStatus();
}

void ProtoLink::startKeepAlive(uint32_t interval)
{
	m_pLinkImp->startKeepAlive(interval);
}

uint32_t ProtoLink::getLastError() const
{
	return m_pLinkImp->getLastError();
}

uint32_t ProtoLink::getPeerIp() const
{
	return m_pLinkImp->getPeerIp();
}

uint32_t ProtoLink::getLocalIp() const
{
	return m_pLinkImp->getLocalIp();
}

uint16_t ProtoLink::getPeerPort() const
{
	return m_pLinkImp->getPeerPort();
}

uint16_t ProtoLink::getLocalPort() const
{
	return m_pLinkImp->getLocalPort();
}

uint32_t ProtoLink::getConnId() const
{
	return m_pLinkImp->getConnId();
}

void		ProtoLink::addRtt(int rtt)
{
	m_pLinkImp->addRtt(rtt);
}

uint32_t	ProtoLink::getAvgRtt() const
{
	return m_pLinkImp->getAvgRtt();
}

uint32_t	ProtoLink::getLastRtt() const
{
	return m_pLinkImp->getLastRtt();
}

bool ProtoLink::isConnected() const
{
	return m_pLinkImp->isConnected();
}

bool ProtoLink::isConnecting() const
{
	return m_pLinkImp->isConnecting();
}

bool ProtoLink::isReady() const
{
	return m_pLinkImp->isReady();
}

bool ProtoLink::isTcpLink() const
{
	return m_pLinkImp->isTcpLink();
}

bool ProtoLink::isSameLink(uint32_t connId) const
{
	return m_pLinkImp->isSameLink(connId);
}

uint32_t ProtoLink::getLastRecvTime() const
{
	return m_pLinkImp->getLastRecvTime();
}

uint64_t ProtoLink::getRecvBytes() const
{
	return m_pLinkImp->getRecvBytes();
}

IProtoLinkHandler*	ProtoLink::getLinkHandler()
{
	//return dynamic_cast<IProtoLinkHandler*>(this);
	return m_pLinkImp->getLinkHandler();
}

//ProtoTcpLink:
ProtoTcpLink::ProtoTcpLink(int encKey, IProtoLinkHandler* handler) : ProtoLink(TCP_LINK, encKey, handler)
{
}

//ProtoUdpLink:
ProtoUdpLink::ProtoUdpLink(int encKey, IProtoLinkHandler* handler) : ProtoLink(UDP_LINK, encKey, handler)
{
}

