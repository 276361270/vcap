#ifndef FFMLOG_H
#define FFMLOG_H

#include <iostream>
#include <string>
#include <fstream>

inline void LOG_INIT() 
{
	std::ofstream *ofs = new std::ofstream("d:\\ffmfilter.log");
	std::cout.rdbuf(ofs->rdbuf());
}

template<typename T>
inline void FFMLOG(T msg)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " <<msg;
	std::cout<<"[ffmfilter] - "<<::GetTickCount()<<"- "<<msg<<std::endl;
}

template<typename T>
inline void FFMLOG(std::string msg, T value)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value;
	std::cout<<"[ffmfilter] - "<<::GetTickCount()<<"- "<<msg<<" "<<value<<std::endl;
}

template<typename T1, typename T2>
inline void FFMLOG(std::string msg, T1 value1, T2 value2)
{
//   LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value1 <<", " <<value2;
	std::cout<<"[ffmfilter] - "<<::GetTickCount()<<"- "<<msg<<" "<<value1<<", "<<value2<<std::endl;
}

template<typename T1, typename T2, typename T3>
inline void FFMLOG(std::string msg, T1 value1, T2 value2, T3 value3)
{
//    LogFinal(LOG::KProtocolSession)<<"[sess] " << msg << " " << value1 <<", " <<value2 <<", " <<value3;
	std::cout<<"[ffmfilter] - "<<::GetTickCount()<<"- "<<msg<<" "<<value1<<", "<<value2<<", "<<value3<<std::endl;
}



#endif
