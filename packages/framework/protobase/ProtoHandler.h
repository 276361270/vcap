#ifndef	PROTOHANDLER_H
#define PROTOHANDLER_H

#include "ProtoConfig.h"
#include <map>

#pragma warning(disable: 4251)

class IProtoPacket;
template<typename T>
class SESSCOMM_API ProtoHandler
{
public:
	typedef void (T::*event_handler)(IProtoPacket*);
	typedef std::map<unsigned int, event_handler>	handler_map;

public:
	ProtoHandler(T* handler);

public:
	void	addHandler(unsigned int uri, event_handler handler);
	void	handle(IProtoPacket* proto);

private:
	handler_map	mHandlers;
	T* _protoHandler;
};

template<typename T>
ProtoHandler<T>::ProtoHandler(T* handler)
:_protoHandler(handler)
{

}

template<typename T>
void	ProtoHandler<T>::addHandler(unsigned int uri, event_handler handler)
{
	mHandlers[uri] = handler;
}

template<typename T>
void	ProtoHandler<T>::handle(IProtoPacket* proto)
{
	if( !proto )
		return;

#ifdef _WIN32
    handler_map::const_iterator it = mHandlers.find(proto->getUri());
	if( it != mHandlers.end() )
	{
		(_protoHandler->*(it->second))(proto);
	}
#endif
}


#endif
