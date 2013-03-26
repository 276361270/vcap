#include "ProtoLinkImp.h"
#include "IProtoLink.h"
#include "ProtoLog.h"
#include "IProtoPacket.h"
//#include "ProtoHandler.h"
#include "ProtoUtils.h"
#include "ProtoHelper.h"
#include "ProtoTime.h"
#include "ProtoA2U.h"

using namespace core;
using namespace core::NetIO;

ProtoLinkImp::ProtoLinkImp(uint32_t ltype, int encKey, IProtoLinkHandler* handler) : mLinkType(ltype), mEncKey(encKey), mLinkHandler(handler)
{
	mConnAttr = NULL;
	mPeerIp = 0;
	m_uLocalIp = 0;
	mConnId = CONNID_INVALID;
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

ProtoLinkImp::~ProtoLinkImp()
{
	mLinkHandler = NULL;
	close();
	NetIO::UnregEvHandler( dynamic_cast<NetIO::IEventHandler*>(this) );

	if( mConnAttr )
	{
		for(uint32_t index = 0; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++ index)
		{
			delete mConnAttr->exts[index];
		}
		delete mConnAttr;
	}
}

void ProtoLinkImp::setProxy(protocol::IProxy* proxy)
{
	m_pProxy = proxy;
}

bool ProtoLinkImp::connect(uint32_t ip, const std::vector<uint16_t>& ports)
{
	mPeerIp = ip;
	mPorts.assign(ports.begin(), ports.end());

	//clear first:
	if( mConnAttr )
	{
		for(uint32_t index = 0; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++ index)
		{
			delete mConnAttr->exts[index];
			mConnAttr->exts[index] = NULL;
		}
		delete mConnAttr;
	}
	mConnAttr = new NetIO::ConnAttr();
	mPeerPort = mPorts.back();
	mPorts.pop_back();

	mConnAttr->ConnType = (isTcpLink()) ? (NetIO::ConnAttr::CONN_TCP) :
					  (NetIO::ConnAttr::CONN_UDP);
	mConnAttr->RemoteIP = mPeerIp;
	mConnAttr->RemotePort = mPeerPort;
	mConnAttr->evHandler = this;

	
	for(uint32_t index = 0; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++ index)
	{
		mConnAttr->exts[index] = NULL;
	}
	
	//enc:
	if( mLinkType == IProtoLink::TCP_LINK )
	{
		NetIO::ExtEncryption* pEpt = new NetIO::ExtEncryption();
		pEpt->CipherType = NetIO::ExtEncryption::RC4;
		pEpt->URI = ((17 << 8) | 4);
		pEpt->ResURI = mEncKey;
		
		int index = 0;
		for(; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++index)
		{
			if(mConnAttr->exts[index] == NULL)
				break;
		}
		if( index == NetIO::ConnAttr::MAX_EXTENSIONS )
		{
			//PLOG("ProtoLinkImp::open, max extension, shouldnt ever happen.");
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
			NetIO::ExtProxy* pEp = new NetIO::ExtProxy();
			pEp->Type = (proxyInfo.proxyType == protocol::SOCKS_PROXY) ?
				(NetIO::ExtProxy::SOCK5) : (NetIO::ExtProxy::HTTP);
			pEp->Port = proxyInfo.port;
			std::string strIp = ProtoA2U::app2net(proxyInfo.ip);
			pEp->Ip = (int) sox::aton_addr(strIp);
			if(pEp->Ip == INADDR_NONE)
			{
				LPHOSTENT lphost = gethostbyname(strIp.c_str());
				if(lphost != NULL)
				{
					pEp->Ip = ((LPIN_ADDR)lphost->h_addr)->s_addr;
				}
			}
			strcpy(pEp->username, ProtoA2U::app2net(proxyInfo.user).c_str());
			strcpy(pEp->passwd, ProtoA2U::app2net(proxyInfo.password).c_str());

			int index = 0;
			for(; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++index)
			{
				if(mConnAttr->exts[index] == NULL)
					break;
			}
			if( index == NetIO::ConnAttr::MAX_EXTENSIONS )
			{
				//PLOG("ProtoLinkImp::open, max extension, shouldnt ever happen.");
				return false;
			}
			mConnAttr->exts[index] = pEp;
		}
	}		

	mConnId = NetIO::ConnCreate(mConnAttr, 0);	

	mStartConnTime = ProtoTime::currentSystemTime();
	NetIO::ConnConnect(mConnId);

	
	mStatus = IProtoLink::LINK_CONNECTING;		
	//for(uint32_t index = 0; index < NetIO::ConnAttr::MAX_EXTENSIONS; ++ index)
	//{
	//	delete pAttr->exts[index];
	//}
	//delete pAttr;
	return true;
}

bool ProtoLinkImp::connect(std::string server, const std::vector<uint16_t>& ports)
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

bool	ProtoLinkImp::reconnect()
{
	std::vector<uint16_t> ports;

	mPorts.push_back(mPeerPort);
	ports.assign(mPorts.begin(), mPorts.end());
	
	return connect(mPeerIp, ports);	
}

void ProtoLinkImp::send(IProtoPacket* proto)
{	
	if( proto == NULL )
		return;

	//if(mStatus == IProtoLink::LINK_CONNECTED) // Status check should be and is done in higher level. Be consistent with other two "send" functions
	{
		send(proto->getData(), proto->getLength());
	}	
	//else
	{
		//std::string req;
		//req.assign(proto->getData(), proto->getLength());

		//mSavedRequests.push_back(req);
	}
}

void ProtoLinkImp::send(const char* data, uint32_t len)
{	
	NetIO::Packet* pk = NetIO::PacketAlloc(len);
	memcpy(pk->Data, data, len);
	NetIO::ConnSend(mConnId, pk, 0);
	NetIO::PacketRelease(pk);	
}

void ProtoLinkImp::send(uint32_t uri, sox::Marshallable& req)
{
	const std::string& str = ProtoHelper::ProtoToString(uri, req);
	send(str.data(), str.length());
}

void ProtoLinkImp::close()
{
	mStatus = IProtoLink::LINK_CLOSED;
	NetIO::ConnClose(mConnId);	

	//mOldConnIds.push_back(mConnId);
	//mConnId = CONNID_INVALID;	
}

void		ProtoLinkImp::setStatus(uint32_t status)
{
	mStatus = status;
}

uint32_t	ProtoLinkImp::getStatus()
{
	return mStatus;
}

void ProtoLinkImp::startKeepAlive(uint32_t interval)
{
	//need a timer thing.
	//core::NetIO::SetTimeout(mConnId);
}

void ProtoLinkImp::onConnected()
{
	if( mLinkHandler )
		mLinkHandler->onConnected();
}

void ProtoLinkImp::onError()
{
	if( mLinkHandler )
		mLinkHandler->onError();
}

void ProtoLinkImp::onClosed()
{
	if( mLinkHandler )
		mLinkHandler->onClosed();
}

void ProtoLinkImp::onKeepAlive()
{
	if( mLinkHandler )
		mLinkHandler->onKeepAlive();
}

void ProtoLinkImp::onTimer(int id)
{
	if( mLinkHandler )
		mLinkHandler->onTimer(id);
}

int	ProtoLinkImp::OnEvent(CNetEvent evt, Packet* pkt)
{
	switch( evt.EvtType )
	{
		case CNetEvent::EV_CONNECTED:
			{	
				mFinishConnTime = ProtoTime::currentSystemTime();
				addRtt( mFinishConnTime - mStartConnTime );
				mStatus = IProtoLink::LINK_CONNECTED;
				this->onConnected();				
			}
			break;
		/*
		case CNetEvent::EV_DISCONNECTED:
			{	
				mStatus = IProtoLink::LINK_DISCONNECTED;	
				close();
                this->onClosed();
			}
			break;
		*/
		case CNetEvent::EV_ERROR:
			{			
				PLOG("ProtoLinkImp::onEvent, error=", evt.RetVal);
				mStatus = IProtoLink::LINK_ERROR;

				close();
                onError();

			}
			break;
		case CNetEvent::EV_IN:
			{
				if( pkt )
				{
					m_uLastRecvTime = pkt->timestamp;
					m_uRecvBytes += pkt->DataLen;
					if( mLinkHandler )
					{
						mLinkHandler->onData(pkt->Data, pkt->DataLen);
					}
					else
					{
					}
					PacketRelease(pkt);
				}
			}
			break;
		case CNetEvent::EV_ALIVE:
			{
				//this->onAlive();
			}
			break;
		case CNetEvent::EV_SENT:
			break;
		case CNetEvent::EV_NETWORKLOST:
			break;
		case CNetEvent::EV_NETWORKRESUME:
			reconnect();
			break;
		default:
			//assert(false);
			break;
	}    
    
	return 0;
}

uint32_t ProtoLinkImp::getLastError() const
{
	return m_uLastError;
}

uint32_t ProtoLinkImp::getPeerIp() const
{
	return mPeerIp;
}

uint32_t ProtoLinkImp::getLocalIp() const
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

uint16_t ProtoLinkImp::getPeerPort() const
{
	return mPeerPort;
}

uint16_t ProtoLinkImp::getLocalPort() const
{
	return m_uLocalPort;
}

uint32_t ProtoLinkImp::getConnId() const
{
	if( mConnId != CONNID_INVALID )
		return mConnId;
	else if( mOldConnIds.size() > 0 )
	{
		return mOldConnIds[mOldConnIds.size()-1];
	}

	return CONNID_INVALID;
}

void		ProtoLinkImp::addRtt(int rtt)
{
	//mRtts.push_back(rtt);
	mRttSum += rtt;
	mRttSize += 1;
	mRttLast = rtt;
}

uint32_t	ProtoLinkImp::getAvgRtt() const
{
	return (uint32_t)mRttSum/mRttSize;
}

uint32_t	ProtoLinkImp::getLastRtt() const
{
	return mRttLast;
}

bool ProtoLinkImp::isConnected() const
{
	return (mStatus == IProtoLink::LINK_CONNECTED);
}

bool ProtoLinkImp::isConnecting() const
{
	return (mStatus == IProtoLink::LINK_CONNECTING );
}

bool ProtoLinkImp::isReady() const
{
	return (mStatus == IProtoLink::LINK_READY );
}

bool ProtoLinkImp::isTcpLink() const
{
	return (mLinkType == IProtoLink::TCP_LINK);
}

bool ProtoLinkImp::isSameLink(uint32_t connId) const
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

uint32_t ProtoLinkImp::getLastRecvTime() const
{
	return m_uLastRecvTime;
}

uint64_t ProtoLinkImp::getRecvBytes() const
{
	return m_uRecvBytes;
}

IProtoLinkHandler*	ProtoLinkImp::getLinkHandler()
{
	return mLinkHandler;
}
