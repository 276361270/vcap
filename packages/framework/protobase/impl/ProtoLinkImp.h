#ifndef	PROTOLINKIMP_H
#define PROTOLINKIMP_H

#pragma warning(disable:4996)
#define WIN32_LEAN_AND_MEAN

#include "ProtoConfig.h"

#ifdef _WIN32
#include <netio/netio.h>
#endif

#include <vector>

namespace core
{
namespace NetIO
{
	struct ConnAttr;
}
}

namespace protocol
{
	struct IProxy;
}

class IProtoPacket;
class IProtoLinkHandler;
class ProtoLinkImp : public core::NetIO::IEventHandler	
{
public:
	ProtoLinkImp(uint32_t ltype, int encKey, IProtoLinkHandler* handler);
	virtual ~ProtoLinkImp();

public:
	void		setProxy(protocol::IProxy* proxy);
	bool		connect(uint32_t ip, const std::vector<uint16_t>& ports);
	bool		connect(std::string server, const std::vector<uint16_t>& ports);
	bool		reconnect();
	void		send(IProtoPacket* proto);
	void		send(const char* data, uint32_t len);
	void		send(uint32_t uri, sox::Marshallable& req);
	void		close();
	void		setStatus(uint32_t status);
	uint32_t	getStatus();
	void		startKeepAlive(uint32_t interval);

	//ILinkHandler
	void		onConnected();	
	void		onError();
	void		onClosed();
	void		onKeepAlive();
	void		onTimer(int id);

	//core::NetIO::IEventHandler
	virtual int	OnEvent(core::NetIO::CNetEvent evt, core::NetIO::Packet* pkt);	

	uint32_t	getLastError() const;
	uint32_t	getPeerIp() const;
	uint32_t	getLocalIp() const;
	uint16_t	getPeerPort() const;
	uint16_t	getLocalPort() const;
	uint32_t	getConnId() const;
	void		addRtt(int rtt);
	uint32_t	getAvgRtt() const;
	uint32_t	getLastRtt() const;
	bool		isConnected() const;
	bool		isConnecting() const;
	bool		isReady() const;
	bool		isTcpLink() const;	
	bool		isSameLink(uint32_t connId) const;
	uint32_t	getLastRecvTime() const;
	uint64_t	getRecvBytes() const;
	IProtoLinkHandler*	getLinkHandler();

private:
	//ProtoTimer<ProtoLink> mPingTimer;
	IProtoLinkHandler*	mLinkHandler;
	core::NetIO::ConnAttr*	mConnAttr;
	std::vector<uint16_t> mPorts;
	uint32_t	mEncKey;
	uint32_t	mPeerIp;
	uint32_t	m_uLocalIp;
	uint32_t	mConnId;		//must be private, other class call getConnId.
	std::vector<uint32_t>	mOldConnIds;
	uint32_t	m_uLastRecvTime;
	uint64_t	m_uRecvBytes;
	uint32_t	mStartConnTime;
	uint32_t	mFinishConnTime;
	uint16_t	mPeerPort;
	uint16_t	m_uLocalPort;
	uint32_t	m_uLastError;	
	uint32_t	mRetryTimes;	
	uint32_t	mStatus;
	uint32_t	mLinkType;
	
	uint64_t	mRttSum;
	//std::vector<uint32_t>		mRtts;
	uint32_t	mRttLast;
	uint32_t	mRttSize;
	//std::vector<std::string>	mSavedRequests;
	protocol::IProxy*	m_pProxy;
};

#endif
