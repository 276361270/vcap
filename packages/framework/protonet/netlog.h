#ifndef _NETLOG_H
#define _NETLOG_H

//#include "dwbase/log.h"
#include <iostream>

//#ifdef _DEBUG
template<typename T>
inline void NET_LOG(T msg)
{
//	LogFinal(LOG::KProtocolNet)<<"[netmod] " <<msg;
}

template<typename T>
inline void NET_LOG(std::string msg, T value)
{
//	LogFinal(LOG::KProtocolNet)<<"[netmod] " << msg << " " << value;
}

template<typename T1, typename T2>
inline void NET_LOG(std::string msg, T1 value1, T2 value2)
{
//	LogFinal(LOG::KProtocolNet)<<"[netmod] " << msg << " " << value1 <<", " <<value2;
}

template<typename T1, typename T2, typename T3>
inline void NET_LOG(std::string msg, T1 value1, T2 value2, T3 value3)
{
//	LogFinal(LOG::KProtocolNet)<<"[netmod] " << msg << " " << value1 <<", " <<value2 <<", " <<value3;
}

#endif