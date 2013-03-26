#ifndef	PROTOLINK_H
#define PROTOLINK_H

#pragma warning(disable:4996)

#define WIN32_LEAN_AND_MEAN

#include "IProtoLink.h"
#include <vector>

class IProtoPacket;
class ProtoLinkImp;
class ProtoUnixLinkImp;
class SESSCOMM_API ProtoLink : public IProtoLink
{
public:
	ProtoLink(LinkType ltype, int encKey, IProtoLinkHandler* handler);
	virtual ~ProtoLink();

public:
	virtual void		setProxy(protocol::IProxy* proxy);
	virtual bool		connect(uint32_t ip, const std::vector<uint16_t>& ports);
	virtual bool		connect(std::string server, const std::vector<uint16_t>& ports);
	virtual bool		reconnect();
	virtual void		send(IProtoPacket* proto);
	virtual void		send(const char* data, uint32_t len);		
	virtual void		send(uint32_t uri, sox::Marshallable& req);
	virtual void		close();
	virtual void		setStatus(IProtoLink::LinkStatus status);
	virtual IProtoLink::LinkStatus	getStatus();
	virtual void		startKeepAlive(uint32_t interval);

	virtual uint32_t	getLastError() const;
	virtual uint32_t	getPeerIp() const;
	virtual uint32_t	getLocalIp() const;
	virtual uint16_t	getPeerPort() const;
	virtual uint16_t	getLocalPort() const;
	virtual uint32_t	getConnId() const;
	virtual void		addRtt(int rtt);
	virtual uint32_t	getAvgRtt() const;
	virtual uint32_t	getLastRtt() const;
	virtual bool		isConnected() const;
	virtual bool		isConnecting() const;
	virtual bool		isReady() const;
	virtual bool		isTcpLink() const;	
	virtual bool		isSameLink(uint32_t connId) const;
	virtual uint32_t	getLastRecvTime() const;
	virtual uint64_t	getRecvBytes() const;
	virtual IProtoLinkHandler*	getLinkHandler();

private:
/*
#ifdef WIN32
     ProtoLinkImp*	m_pLinkImp;
#else
     ProtoUnixLinkImp* m_pLinkImp;
#endif
*/
	ProtoUnixLinkImp* m_pLinkImp;
};

class SESSCOMM_API ProtoTcpLink : public ProtoLink
{
public:
	ProtoTcpLink(int encKey, IProtoLinkHandler* handler);
};

class SESSCOMM_API ProtoUdpLink : public ProtoLink
{
public:
	ProtoUdpLink(int encKey, IProtoLinkHandler* handler);
};


#endif
