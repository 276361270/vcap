#include "linklayerenc.h"
#include "conn.h"

static const char rnd_seed[] = "string to make the random number generator think it has entropy";
RSA* LinkLayerEnc::m_RSAKey = NULL;

LinkLayerEnc::LinkLayerEnc()
{
    m_status = STATUS_NEW;
}

LinkLayerEnc::~LinkLayerEnc()
{

}

int LinkLayerEnc::init(Extension* pExt)
{
    m_uExtID = pExt->extID;

    ExtEncryption* pEnc = (ExtEncryption*)pExt;

    m_URIreq = pEnc->URI;
    m_URIres = pEnc->ResURI;
    return 0;
}

int LinkLayerEnc::send(char* data, int len)
{
    if (m_status != STATUS_ENC)
        return -1;

    // decrypt and send up
    //DW_RC4(&m_sendKey, len, (unsigned char*)data, (unsigned char*)data);
	RC4(&m_sendKey, len, (unsigned char*)data, (unsigned char*)data);

    if (m_pNextLayer) {
        return m_pNextLayer->send(data, len);
    }
    else {
        return m_pOwner->_send(data, len);
    }
}

int LinkLayerEnc::onConnected()
{
    int n = sizeof(struct _PExchangeKey);
    n++;
    _PExchangeKey* pExKey = (_PExchangeKey*)malloc( sizeof(struct _PExchangeKey) );
    pExKey->uri = m_URIreq;
    pExKey->ResCode = 200;
    //pExKey->plen = DW_BN_bn2bin(m_RSAKey->n, pExKey->pubKey);
    //pExKey->elen = DW_BN_bn2bin(m_RSAKey->e, pExKey->e);
	pExKey->plen = BN_bn2bin(m_RSAKey->n, pExKey->pubKey);
	pExKey->elen = BN_bn2bin(m_RSAKey->e, pExKey->e);
    pExKey->len  = 14 + pExKey->plen + pExKey->elen; // to change

    m_status = STATUS_INIT;

    if (m_pNextLayer)
        m_pNextLayer->send((char*)pExKey, pExKey->len);
    else
        m_pOwner->_send((char*)pExKey, pExKey->len);
    return 0;
}

int LinkLayerEnc::onData(inputbuf_t& input, size_t nrecv)
{
    if ( m_status == STATUS_NEW )
    {
        input.erase( input.size()-nrecv, nrecv);
        return m_pOwner->_onError();
    }
    else if ( m_status == STATUS_INIT )
    {
        _PExchangeKeyRes* pExRes = (_PExchangeKeyRes*)(input.tail()-nrecv);
        if (nrecv < sizeof(_PExchangeKeyRes) || pExRes->uri != m_URIres)
        {
            input.erase( input.size()-nrecv, nrecv);
            return m_pOwner->_onError();
        }
        // decode the key and set rc4 key
        unsigned char key[64];
        //int num = DW_RSA_private_decrypt(pExRes->keylen, pExRes->sesKey, key, m_RSAKey, RSA_PKCS1_PADDING);
		int num = RSA_private_decrypt(pExRes->keylen, pExRes->sesKey, key, m_RSAKey, RSA_PKCS1_PADDING);
        if (num != SESSIONKEY_LENGTH)
        {
            input.erase( input.size()-nrecv, nrecv);
            return m_pOwner->_onError();
        }

        //DW_RC4_set_key(&m_sendKey, SESSIONKEY_LENGTH, key);
        //DW_RC4_set_key(&m_recvKey, SESSIONKEY_LENGTH, key);
		RC4_set_key(&m_sendKey, SESSIONKEY_LENGTH, key);
		RC4_set_key(&m_recvKey, SESSIONKEY_LENGTH, key);

        m_status = STATUS_ENC;        
		NET_LOG("LinkLayerEnc::onData, RSA done.");

        // this layer is ready, call next layer's OnConnect
        if (m_pPreLayer) 
            m_pPreLayer->onConnected();
        else
            m_pOwner->_onConnected();

        // if we have more data, call self's OnData to dec
        if (nrecv > pExRes->len) 
        {
            input.erase( input.size()-nrecv, pExRes->len );
            return this->onData( input, (nrecv - pExRes->len) );
        }
        else
            input.erase( input.size()-nrecv, nrecv );
    }
    else
    {
        // decrypt and send up
        //DW_RC4(&m_recvKey, nrecv, (unsigned char*)input.tail()-nrecv, (unsigned char*)input.tail()-nrecv);
		RC4(&m_recvKey, nrecv, (unsigned char*)input.tail()-nrecv, (unsigned char*)input.tail()-nrecv);
        if (m_pPreLayer) {
            return m_pPreLayer->onData(input, nrecv);
        }
        else {
            return m_pOwner->_onData();
        }
    }
    return 0;
}

void LinkLayerEnc::genRSAKey()
{
	/*
    DW_RAND_seed(rnd_seed, sizeof(rnd_seed) );
    m_RSAKey = DW_RSA_generate_key(512, 3, NULL, NULL);
    
    while(DW_RSA_check_key(m_RSAKey) != 1)
    {
        DW_RSA_free(m_RSAKey);
        m_RSAKey = DW_RSA_generate_key(512, 3, NULL, NULL);
    }
	*/
    RAND_seed(rnd_seed, sizeof(rnd_seed) );
    m_RSAKey = RSA_generate_key(512, 3, NULL, NULL);
    
    while(RSA_check_key(m_RSAKey) != 1)
    {
        RSA_free(m_RSAKey);
        m_RSAKey = RSA_generate_key(512, 3, NULL, NULL);
    }
}

