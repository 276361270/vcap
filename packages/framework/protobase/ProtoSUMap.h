#ifndef PROTOSUMAP_H
#define PROTOSUMAP_H

#include "ProtoConfig.h"
#include "ProtoUList.h"
#include <map>
#include <set>


class SESSCOMM_API ProtoSUMap
{
public:
	//typedef std::map<uint32_t, ProtoUList>	umap_type;
	typedef std::set<uint32_t>	suset_type;
	typedef std::map<uint32_t, suset_type>	sumap_type;

public:
	ProtoSUMap();
	~ProtoSUMap();

public:
	void	add(uint32_t sid, uint32_t uid);
	void	add(uint32_t sid, const std::vector<uint32_t>& uids);
	void	add(uint32_t sid, const std::set<uint32_t>& uids);
	void	add(const sumap_type& map);
	void	add(const std::map<uint32_t, std::vector<uint32_t> >& partners);	//sid, uid list
	void	add(const std::map<uint32_t, uint32_t>& partners);	//uid, sid.
	void	remove(uint32_t sid, uint32_t uid);
	void	clear();
	bool	find(uint32_t sid, uint32_t uid);
	void	fetch(uint32_t pid, std::vector<uint32_t>& uids, uint32_t max);
	
private:
	sumap_type	m_arrUserMap;
};

#endif