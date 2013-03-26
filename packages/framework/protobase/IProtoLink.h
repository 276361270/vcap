#ifndef IPROTOLINK_H
#define IPROTOLINK_H

#include "ProtoConfig.h"
#include <vector>

class IProtoPacket;
class IProtoLinkHandler;
class IProtoLink;
class SESSCOMM_API IProtoLink
{
public:
	enum LinkStatus
	{
		LINK_INITED = 0,
		LINK_CONNECTING,
		LINK_PENDING,
		LINK_CONNECTED,
		LINK_DISCONNECTED,
		LINK_RECONNECTING,
		LINK_CLOSED,
		LINK_ERROR,
		LINK_READY,
	};

	enum LinkType
	{
		TCP_LINK,
		UDP_LINK,
        LINK_TYPE_NUM
	};	
public:
	virtual ~IProtoLink(){}

public:
	virtual bool		connect(uint32_t ip, const std::vector<uint16_t>& ports) = 0;
	virtual bool		connect(std::string server, const std::vector<uint16_t>& ports) = 0;
	virtual bool		reconnect() = 0;
	virtual void		send(IProtoPacket* proto) = 0;
	virtual void		send(const char* data, uint32_t len) = 0;	
	virtual void		send(uint32_t uri, sox::Marshallable& req) = 0;
	virtual void		close() = 0;
	virtual void		setStatus(LinkStatus status) = 0;
	virtual LinkStatus	getStatus() = 0;
	virtual void		startKeepAlive(uint32_t interval) = 0;

	virtual uint32_t	getLastError() const = 0;
	virtual uint32_t	getPeerIp() const = 0;
	virtual uint32_t	getLocalIp() const = 0;
	virtual uint16_t	getPeerPort() const = 0;
	virtual uint16_t	getLocalPort() const = 0;
	virtual uint32_t	getConnId() const = 0;
	virtual void		addRtt(int rtt) = 0;
	virtual uint32_t	getAvgRtt() const = 0;
	virtual uint32_t	getLastRtt() const = 0;
	virtual bool		isConnected() const = 0;
	virtual bool		isConnecting() const = 0;
	virtual bool		isReady() const = 0;
	virtual bool		isTcpLink() const = 0;	
	virtual bool		isSameLink(uint32_t connId) const = 0;
	virtual uint32_t	getLastRecvTime() const = 0;
	virtual uint64_t	getRecvBytes() const = 0;
	virtual IProtoLinkHandler*	getLinkHandler() = 0;
};


class SESSCOMM_API IProtoLinkHandler
{
public:
	virtual void onConnected() = 0;	
	virtual void onError() = 0;	
	virtual void onClosed() = 0;
	virtual void onKeepAlive() = 0;
	virtual void onTimer(int id) = 0;
	virtual void onData(const char* data, int len) = 0;
};


#endif
