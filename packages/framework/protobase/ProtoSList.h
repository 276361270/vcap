#ifndef PROTOSLIST_H
#define PROTOSLIST_H

#include "ProtoConfig.h"
#include <deque>

class SESSCOMM_API ProtoSList
{
public:
	ProtoSList();

public:
	void	add(uint32_t sid);
	void	add(const std::vector<uint32_t>& sids);
	void	add(const std::set<uint32_t>& sids);
	void	remove(uint32_t sid);
	void	clear();
	void	sort();
	uint32_t size();
	bool	find(uint32_t sid);

private:
	std::deque<uint32_t>	m_arrSids;
	bool	m_bSorted;

};

#endif