#ifndef PROTOLOG_H
#define PROTOLOG_H

#include "ProtoConfig.h"

template<typename T>
inline void PLOG(T msg)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " <<msg;
	std::cout<<"[sess] - "<<msg;
}

template<typename T>
inline void PLOG(std::string msg, T value)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value;
	std::cout<<"[sess] - "<<msg<<" "<<value;
}

template<typename T1, typename T2>
inline void PLOG(std::string msg, T1 value1, T2 value2)
{
//   LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value1 <<", " <<value2;
	std::cout<<"[sess] - "<<msg<<" "<<value1<<", "<<value2;
}

template<typename T1, typename T2, typename T3>
inline void PLOG(std::string msg, T1 value1, T2 value2, T3 value3)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value1 <<", " <<value2 <<", " <<value3;
	std::cout<<"[sess] - "<<msg<<" "<<value1<<", "<<value2<<", "<<value3;
}



#endif
