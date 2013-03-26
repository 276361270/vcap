#ifndef PROTOSTATDATAIMP_H
#define PROTOSTATDATAIMP_H

#include "ProtoConfig.h"
#include <map>

class ProtoStatDataImp
{
public:
	typedef std::map<uint32_t, uint32_t>	keytime_t;
	typedef keytime_t::iterator	keytime_it_t;
	typedef std::map<uint32_t, keytime_t>	sidkeytime_t;
	typedef sidkeytime_t::iterator	sidkeytime_it_t;

public:
	ProtoStatDataImp();
	~ProtoStatDataImp();

public:
	void		rebind(uint32_t sid, uint32_t asid);
	void		probeTime(uint32_t sid, uint32_t key);
	uint32_t	getTime(uint32_t sid, uint32_t key);
	uint32_t	getSpendTime(uint32_t sid, uint32_t key1, uint32_t key2);
    uint32_t    getSpendTimeUp2Now(uint32_t sid, uint32_t key);

	void		setInt(uint32_t sid, uint32_t type, uint32_t value);
	uint32_t	getInt(uint32_t sid, uint32_t type);
	void		setString(uint32_t sid, uint32_t type, std::string value);
	std::string getString(uint32_t sid, uint32_t type);

	bool		has(uint32_t sid, uint32_t key);
	void		reset(uint32_t sid);

private:
	sidkeytime_t	m_mapSidKeyTime;
};


#endif