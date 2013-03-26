#include "ProtoUnixLinkImp.h"
#include "IProtoLink.h"
#include "ProtoLog.h"
#include "IProtoPacket.h"
#include "ProtoHandler.h"
#include "ProtoUtils.h"
#include "ProtoHelper.h"
#include "ProtoTime.h"
#include "ProtoA2U.h"


ProtoUnixLinkImp::ProtoUnixLinkImp(uint32_t ltype, int encKey, IProtoLinkHandler* handler) : mLinkType(ltype), mEncKey(encKey), mLinkHandler(handler)
{
	mConnAttr = NULL;
	mPeerIp = 0;
	m_uLocalIp = 0;
	mConnId = 0;
	m_uLastRecvTime = 0;
	m_uRecvBytes = 0;
	mStartConnTime = 0;
	mFinishConnTime = 0;
	mPeerPort = 0;
	m_uLocalPort = 0;
	m_uLastError = 0;	
	mRetryTimes = 0;
	
	mStatus = 0;
	mRttSum = 0;
	mRttLast = 0;
	mRttSize = 0;

	m_pProxy = NULL;	
}

ProtoUnixLinkImp::~ProtoUnixLinkImp()
{
	mLinkHandler = NULL;
	close();
    //NetMod::UnregEvHandler( dynamic_cast<IEventHandler*>(this) );

	if( mConnAttr )
	{
        for(uint32_t index = 0; index < NetMod::ConnAttr::MAX_EXTENSIONS; ++ index)
		{
			delete mConnAttr->exts[index];
		}
		delete mConnAttr;
	}
}

void ProtoUnixLinkImp::setProxy(protocol::IProxy* proxy)
{
	m_pProxy = proxy;
}

bool ProtoUnixLinkImp::connect(uint32_t ip, const std::vector<uint16_t>& ports)
{
	mPeerIp = ip;
	mPorts.assign(ports.begin(), ports.end());

	//clear first:
	if( mConnAttr )
	{
        for(uint32_t index = 0; index < NetMod::ConnAttr::MAX_EXTENSIONS; ++ index)
		{
			delete mConnAttr->exts[index];
			mConnAttr->exts[index] = NULL;
		}
		delete mConnAttr;
	}
    mConnAttr = new NetMod::ConnAttr();
	mPeerPort = mPorts.back();
	mPorts.pop_back();

    mConnAttr->ConnType = (isTcpLink()) ? (NetMod::ConnAttr::CONN_TCP) :
        (NetMod::ConnAttr::CONN_UDP);
	mConnAttr->RemoteIP = mPeerIp;
	mConnAttr->RemotePort = mPeerPort;
	mConnAttr->evHandler = this;

	
    for(uint32_t index = 0; index < NetMod::ConnAttr::MAX_EXTENSIONS; ++ index)
	{
		mConnAttr->exts[index] = NULL;
	}
	
	//enc:
	if( mLinkType == IProtoLink::TCP_LINK && mEncKey != 0 )
	{
		NetMod::ExtEncryption* pEpt = new NetMod::ExtEncryption();
		pEpt->CipherType = NetMod::ExtEncryption::RC4;
		pEpt->URI = ((17 << 8) | 4);
		pEpt->ResURI = mEncKey;
		
		int index = 0;
        for(; index < NetMod::ConnAttr::MAX_EXTENSIONS; ++index)
		{
			if(mConnAttr->exts[index] == NULL)
				break;
		}
        if( index == NetMod::ConnAttr::MAX_EXTENSIONS )
		{
			//PLOG("ProtoUnixLinkImp::open, max extension, shouldnt ever happen.");
			return false;
		}
		mConnAttr->exts[index] = pEpt;
	}

	//proxy:
	if(  mLinkType == IProtoLink::TCP_LINK && m_pProxy )
	{
		protocol::NetworkProxyInfo proxyInfo = m_pProxy->getProxyInfo();
		if(proxyInfo.proxyType != protocol::NO_PROXY)
		{
            NetMod::ExtProxy* pEp = new NetMod::ExtProxy();
			pEp->Type = (proxyInfo.proxyType == protocol::SOCKS_PROXY) ?
                (NetMod::ExtProxy::SOCK5) : (NetMod::ExtProxy::HTTP);
			pEp->Port = proxyInfo.port;
			std::string strIp = proxyInfo.ip;
            pEp->Ip = (int) ProtoHelper::IPToUint32(strIp);
			if(pEp->Ip == INADDR_NONE)
			{
                hostent* lphost = gethostbyname(strIp.c_str());
				if(lphost != NULL)
				{
                    pEp->Ip = ((in_addr*)lphost->h_addr)->s_addr;
				}
			}
			strcpy(pEp->username, proxyInfo.user.c_str());
			strcpy(pEp->passwd, proxyInfo.password.c_str());

			int index = 0;
            for(; index < NetMod::ConnAttr::MAX_EXTENSIONS; ++index)
			{
				if(mConnAttr->exts[index] == NULL)
					break;
			}
            if( index == NetMod::ConnAttr::MAX_EXTENSIONS )
			{
				//PLOG("ProtoUnixLinkImp::open, max extension, shouldnt ever happen.");
				return false;
			}
			mConnAttr->exts[index] = pEp;
		}
	}		

    mConnId = NetMod::ConnCreate(mConnAttr);	

	mStartConnTime = ProtoTime::currentSystemTime();
    NetMod::ConnConnect(mConnId);

	
	mStatus = IProtoLink::LINK_CONNECTING;		
	//for(uint32_t index = 0; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++ index)
	//{
	//	delete pAttr->exts[index];
	//}
	//delete pAttr;
	return true;
}

bool ProtoUnixLinkImp::connect(std::string server, const std::vector<uint16_t>& ports)
{
	std::string strIp;	
	std::vector<uint32_t>	ips;

	if( !ProtoUtils::GetHostIp(server.c_str(), strIp, ips) )
	{
		return false;
	}

	if( ips.size() == 0 )
	{
		return false;
	}
	std::random_shuffle(ips.begin(), ips.end());

	return connect( ips[0], ports);
}

bool	ProtoUnixLinkImp::reconnect()
{
	std::vector<uint16_t> ports;

	mPorts.push_back(mPeerPort);
	ports.assign(mPorts.begin(), mPorts.end());
	
	return connect(mPeerIp, ports);	
}

void ProtoUnixLinkImp::send(IProtoPacket* proto)
{	
	if( proto == NULL )
		return;

	if(mStatus == IProtoLink::LINK_CONNECTED)
	{
		send(proto->getData(), proto->getLength());
	}	
	else
	{
		//std::string req;
		//req.assign(proto->getData(), proto->getLength());

		//mSavedRequests.push_back(req);
	}
}

void ProtoUnixLinkImp::send(const char* data, uint32_t len)
{	
    NetMod::Packet* pk = NetMod::PacketAlloc(data, len);
    NetMod::ConnSend(mConnId, pk);
    NetMod::PacketRelease(pk);	
}

void ProtoUnixLinkImp::send(uint32_t uri, sox::Marshallable& req)
{
	const std::string& str = ProtoHelper::ProtoToString(uri, req);
	send(str.data(), str.length());
}

void ProtoUnixLinkImp::close()
{
	mStatus = IProtoLink::LINK_CLOSED;
    NetMod::ConnClose(mConnId);	

	//mOldConnIds.push_back(mConnId);
	//mConnId = CONNID_INVALID;	
}

void		ProtoUnixLinkImp::setStatus(uint32_t status)
{
	mStatus = status;
}

uint32_t	ProtoUnixLinkImp::getStatus()
{
	return mStatus;
}

void ProtoUnixLinkImp::startKeepAlive(uint32_t interval)
{
	//need a timer thing.
	//core::NetIO::SetTimeout(mConnId);
}

void ProtoUnixLinkImp::onConnected()
{
	if( mLinkHandler )
		mLinkHandler->onConnected();
}

void ProtoUnixLinkImp::onError()
{
	if( mLinkHandler )
		mLinkHandler->onError();
}

void ProtoUnixLinkImp::onClosed()
{
	if( mLinkHandler )
		mLinkHandler->onClosed();
}

void ProtoUnixLinkImp::onKeepAlive()
{
	if( mLinkHandler )
		mLinkHandler->onKeepAlive();
}

void ProtoUnixLinkImp::onTimer(int id)
{
	if( mLinkHandler )
		mLinkHandler->onTimer(id);
}

int	ProtoUnixLinkImp::OnEvent(NetMod::CNetEvent evt, NetMod::Packet* pkt)
{
	switch( evt.EvtType )
	{
    case NetMod::CNetEvent::EV_CONNECTED:
			{	
				mFinishConnTime = ProtoTime::currentSystemTime();
				addRtt( mFinishConnTime - mStartConnTime );
				mStatus = IProtoLink::LINK_CONNECTED;
				this->onConnected();				
			}
			break;
    case NetMod::CNetEvent::EV_ERROR:
			{			
				PLOG("ProtoUnixLinkImp::onEvent, error=", evt.RetVal);
				mStatus = IProtoLink::LINK_ERROR;

				close();
                onError();

			}
			break;
    case NetMod::CNetEvent::EV_IN:
			{
				if( pkt )
				{
					m_uLastRecvTime = pkt->_timestamp;
					m_uRecvBytes += pkt->_dataLen;
					if( mLinkHandler )
					{
						mLinkHandler->onData(pkt->_data, pkt->_dataLen);
					}
					else
					{
					}
					PacketRelease(pkt);
				}
			}
			break;
    case NetMod::CNetEvent::EV_ALIVE:
			{
				//this->onAlive();
			}
			break;
    case NetMod::CNetEvent::EV_SENT:
			break;
    case NetMod::CNetEvent::EV_NETWORKLOST:
			break;
    case NetMod::CNetEvent::EV_NETWORKRESUME:
			reconnect();
			break;
		default:
			//assert(false);
			break;
	}    
    
	return 0;
}

uint32_t ProtoUnixLinkImp::getLastError() const
{
	return m_uLastError;
}

uint32_t ProtoUnixLinkImp::getPeerIp() const
{
	return mPeerIp;
}

uint32_t ProtoUnixLinkImp::getLocalIp() const
{
	char host_name[256];
	if(gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
	{
		return 0;
	}
	struct hostent *phe = gethostbyname(host_name);
	if(phe == NULL)
	{
		return 0;
	}
	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	uint32_t localIp = inet_addr(inet_ntoa(addr));
	return localIp;
}

uint16_t ProtoUnixLinkImp::getPeerPort() const
{
	return mPeerPort;
}

uint16_t ProtoUnixLinkImp::getLocalPort() const
{
	return m_uLocalPort;
}

uint32_t ProtoUnixLinkImp::getConnId() const
{
	if( mConnId != 0 )
		return mConnId;
	else if( mOldConnIds.size() > 0 )
	{
		return mOldConnIds[mOldConnIds.size()-1];
	}

	return 0;
}

void		ProtoUnixLinkImp::addRtt(int rtt)
{
	//mRtts.push_back(rtt);
	mRttSum += rtt;
	mRttSize += 1;
	mRttLast = rtt;
}

uint32_t	ProtoUnixLinkImp::getAvgRtt() const
{
	return (uint32_t)mRttSum/mRttSize;
}

uint32_t	ProtoUnixLinkImp::getLastRtt() const
{
	return mRttLast;
}

bool ProtoUnixLinkImp::isConnected() const
{
	return (mStatus == IProtoLink::LINK_CONNECTED);
}

bool ProtoUnixLinkImp::isConnecting() const
{
	return (mStatus == IProtoLink::LINK_CONNECTING );
}

bool ProtoUnixLinkImp::isReady() const
{
	return (mStatus == IProtoLink::LINK_READY );
}

bool ProtoUnixLinkImp::isTcpLink() const
{
	return (mLinkType == IProtoLink::TCP_LINK);
}

bool ProtoUnixLinkImp::isSameLink(uint32_t connId) const
{
	if( connId == mConnId )
		return true;

	for( size_t i=0; i<mOldConnIds.size(); i++ )
	{
		if( mOldConnIds[i] == connId )
			return true;
	}

	return false;
}

uint32_t ProtoUnixLinkImp::getLastRecvTime() const
{
	return m_uLastRecvTime;
}

uint64_t ProtoUnixLinkImp::getRecvBytes() const
{
	return m_uRecvBytes;
}

IProtoLinkHandler*	ProtoUnixLinkImp::getLinkHandler()
{
	return mLinkHandler;
}


