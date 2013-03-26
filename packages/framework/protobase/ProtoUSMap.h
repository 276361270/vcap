#ifndef PROTOUSMAP_H
#define PROTOUSMAP_H

#include "ProtoConfig.h"
#include <map>
#include <vector>

class SESSCOMM_API ProtoUSMap
{
public:
	typedef std::map<uint32_t, uint32_t> umap_type;

public:
	ProtoUSMap();
	~ProtoUSMap();

public:
	void		add(uint32_t uid, uint32_t pid);
	void		add(const std::map<uint32_t, uint32_t>& uids);
	void		remove(uint32_t uid);
	void		change(uint32_t uid, uint32_t pid);
	uint32_t	getPid(uint32_t uid);
	uint32_t	size();
	umap_type&	getMap();
	void		clear();
    uint32_t    fetch(std::vector<uint32_t> &uids, uint32_t max);

private:
	umap_type	m_mapUMap;
};


#endif