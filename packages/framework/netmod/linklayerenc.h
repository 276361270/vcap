#ifndef _LINK_LAYER_ENCRPTO_H_
#define _LINK_LAYER_ENCRPTO_H_
#include "ilinklayer.h"

#include "openssl/rc4.h"
#include "openssl/sha.h"
#include "openssl/md5.h"
#include "openssl/bn.h"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/rand.h"
#include "openssl/crypto.h"
//
#include <openssl/blowfish.h>
#include <openssl/hmac.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/aes.h>
//#include "dwutility/opensslproxy.h"

#define RSA_KEY_LEN 64
#define RC4_KEY_LEN 16
#define SESSIONKEY_LENGTH 16

class LinkLayerEnc
    : public ILinkLayer
{
public:
    LinkLayerEnc();
    virtual ~LinkLayerEnc();

public:
    virtual int init(NetMod::Extension*);
    virtual int send(char* data, int len);
    virtual int onConnected();
    virtual int onData(inputbuf_t& input, size_t nrecv);

public:
    static void genRSAKey();

private:
    RC4_KEY	 m_sendKey;
    RC4_KEY	 m_recvKey;

    uint32_t m_URIreq;
    uint32_t m_URIres;

    enum {STATUS_NEW, STATUS_INIT, STATUS_ENC};
    int		 m_status;

    static RSA* m_RSAKey;

#pragma pack(push)
#pragma pack(1)
    struct _PExchangeKey
    {
        uint32_t	len;
        uint32_t	uri;
        uint16_t	ResCode;
        uint16_t	plen;
        uint8_t	    pubKey[RSA_KEY_LEN];
        uint16_t	elen;
        uint8_t	    e[RSA_KEY_LEN];
    };
    struct _PExchangeKeyRes
    {
        uint32_t	len;
        uint32_t	uri;
        uint16_t	ResCode;
        uint16_t	keylen;
        uint8_t	    sesKey[RC4_KEY_LEN];
    };
#pragma pack (pop)
};

#endif


