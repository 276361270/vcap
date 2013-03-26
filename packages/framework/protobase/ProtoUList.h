#ifndef PROTOULIST_H
#define PROTOULIST_H

#include "ProtoConfig.h"
#include <deque>

class SESSCOMM_API ProtoUList
{
public:
	ProtoUList();
	~ProtoUList();

public:
	void	add(uint32_t uid);
	void	add(const std::vector<uint32_t>& uids);
	void	add(const std::set<uint32_t>& uids);
	void	remove(uint32_t uid);
	void	clear();
	void	sort();
	uint32_t size();
	void	fetch(std::vector<uint32_t>& uids, uint32_t size);
	bool	find(uint32_t uid);

private:
	std::deque<uint32_t>	m_arrUids;
	bool	m_bSorted;

};

#endif
