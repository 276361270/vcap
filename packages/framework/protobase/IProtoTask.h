#ifndef IPROTOTASK_H
#define IPROTOTASK_H

#include "ProtoTime.h"
#include <string>

class IProtoTask
{
public:
	virtual ~IProtoTask(){}
	virtual void	run() = 0;
	virtual void	setRepeat(bool repeat) = 0;
	virtual bool	getRepeat() = 0;
};


template<class T>
class ProtoTimer : public IProtoTask
{
public:
	typedef void (T::*callback)();
public:
	ProtoTimer()
	{
		m_bRepeat = false;
		m_nStart = ProtoTime::currentSystemTime();
	}

	~ProtoTimer()
	{
	}

public:
	virtual void	run()
	{
		(m_pObject->*m_pFunc)();
		m_nEnd = ProtoTime::currentSystemTime() - m_nStart;
		m_nStart += m_nEnd;
	}

	virtual void	setRepeat(bool repeat)
	{
		m_bRepeat = repeat;
	}

	virtual bool	getRepeat()
	{
		return m_bRepeat;
	}


public:
	void init(T* x, callback cb)
	{
		m_pObject = x;
		m_pFunc = cb;
	}

	void init(T* x, callback cb, std::string name)
	{
		m_pObject = x;
		m_pFunc = cb;
		m_strName = name;
	}

	std::string		getName()
	{
		return m_strName;
	}

private:
	unsigned int	m_nStart;
	unsigned int	m_nEnd;
	bool		m_bRepeat;
	T*			m_pObject;
	callback	m_pFunc;
	std::string m_strName;
};



#endif