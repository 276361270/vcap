#ifndef _NET_MODULE_CONNECTION_H_
#define _NET_MODULE_CONNECTION_H_
#include "protonet.h"
#include "blockbuf.h"
#include "ilinklayer.h"
#include <string>

using namespace NetMod;
struct IConn
{
    virtual int onRecv() = 0;
    virtual int onSend() = 0;
};

class CConn
    : public IConn
{
public:
    CConn();
    ~CConn();

public:
    virtual int onRecv();
    virtual int onSend();

public:
    /* return m_connId if sucess, else return -1 */
    int     init(NetMod::ConnAttr* attr);
    /* return 0 if success, else return errno */
    int     connect(uint32_t ip, uint16_t port);
    int     send(char* data, size_t len);
    int     close();

    int     _connect(uint32_t ip, uint16_t port, int sockType);
    int     _send(char* data, size_t len);
    int     _close();

public:
    int     onConnected();
    int     onError();

    int     _onData();
    int     _onSend();
    int     _onConnected();
    int     _onError();

    IEventHandler* getEvHandler() { return m_pEvH; }

private:
    void        setNBlock();
    uint32_t    peeklen(const void* d);
    ILinkLayer* createLayer(Extension* ext);

private:
    SOCKET      m_sockfd;
    int         m_connId;
    int         m_sockType; //SOCK_DGRAM or SOCK_STREAM
    CONNSTATUS  m_status;

    sockaddr_in m_localAddr;
    sockaddr_in m_remoteAddr;

    inputbuf_t  m_input;  //read buffer
    outputbuf_t m_output; //write buffer

    ILinkLayer* m_pFirstLayer;
    ILinkLayer* m_pLastLayer;

    IEventHandler*  m_pEvH;
};

#endif


