#include "ProtoIPMgr.h"
#include "ProtoIPInfo.h"
#include "ProtoLog.h"

#define MAX_IP_RETRY	9

ProtoIPMgr::ProtoIPMgr(uint32_t isp, uint32_t area) : mIspType(isp), mAreaType(area)
{
}

ProtoIPMgr::~ProtoIPMgr()
{
	clear();
}

void		ProtoIPMgr::setIspType(uint32_t isp)
{
	mIspType = isp;
}

void		ProtoIPMgr::setAreaType(uint32_t area)
{
	mAreaType = area;
}

void	ProtoIPMgr::add(ProtoIPInfo* info)
{
	ProtoIPInfo* temp = NULL;

	temp = find( info );
	if( temp == NULL )
	{
		mIPInfos.push_back(info);
	}
	else
	{
		temp->reset();
	}
}

void    ProtoIPMgr::append(ProtoIPInfo* info)
{
    mIPInfos.push_back(info);
}

void	ProtoIPMgr::remove(ProtoIPInfo* info)
{
	if( info == NULL || info->getIP() == 0 || mIPInfos.empty())
		return;

    std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin();
    for (; it != mIPInfos.end(); ++it)  
    {
        ProtoIPInfo* temp = *it;
        if (temp == NULL || temp->getIP() == info->getIP())
        {
            break;
        }
    }

    std::vector<ProtoIPInfo*>::iterator it_base = it;  
    for (; it != mIPInfos.end(); ++it)  
    {  
        ProtoIPInfo* temp = *it;
        if (temp == NULL)
            continue;

        if (temp->getIP() != info->getIP())  
        {
            *it_base = temp;  
            ++it_base;  
        }
        else 
        {     
            //who delete the ip?
            delete temp;
        }
    }  

    mIPInfos.erase(it_base, mIPInfos.end());  
	//for(  = mIPInfos.begin(); it != mIPInfos.end(); )
	//{
	//	ProtoIPInfo* temp = *it;

	//	if(temp != NULL && temp->getIP() == info->getIP() )
	//	{
	//		mIPInfos.erase( it );

	//		//who delete the ip?
	//		delete temp;
 //           continue;
	//	}

 //       ++it;
	//}
}

ProtoIPInfo*	ProtoIPMgr::find(ProtoIPInfo* info)
{
	return find(info->getIP(), info->isTcp());
}

ProtoIPInfo*	ProtoIPMgr::find(uint32_t ip, bool tcp)
{
	for( std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin(); it != mIPInfos.end(); ++it )
	{
		ProtoIPInfo* temp = *it;
		if( temp == NULL )
			continue;

		if( temp->getIP() == ip && temp->isTcp() == tcp )
		{
			return temp;
		}
	}

	return NULL;
}

uint32_t	ProtoIPMgr::getGroup(uint32_t ip, bool tcp)
{
	ProtoIPInfo* info = find(ip, tcp);
	if( info )
		return info->getGroup();

	return 0;
}

void	ProtoIPMgr::clear()
{
	for( std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin(); it != mIPInfos.end(); ++it )
	{
		ProtoIPInfo* temp = *it;
		if( temp == NULL )
			continue;

		delete temp;
	}

	mIPInfos.clear();
	mUsedIPInfos.clear();
}

int		ProtoIPMgr::getCount()
{
	return (int)mIPInfos.size();
}

void	ProtoIPMgr::reset()
{
	for( std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin(); it != mIPInfos.end(); ++it )
	{
		ProtoIPInfo* temp = *it;
		if( temp == NULL )
			continue;

		temp->reset();
	}
}

void	ProtoIPMgr::setUsed(ProtoIPInfo* info, bool used)
{
	ProtoIPInfo* temp = NULL;

	temp = find( info );
	if( temp != NULL )
	{		
		temp->setUsed(used);
		
		if( used )
		{
			mUsedIPInfos.push_back(temp);
		}
		else
		{
			for( std::vector<ProtoIPInfo*>::iterator it = mUsedIPInfos.begin(); it != mUsedIPInfos.end(); ++it )
			{
				ProtoIPInfo* tempused = *it;
				if( tempused == NULL )
					continue;

				if( tempused->getIP() == info->getIP() )
				{
					mUsedIPInfos.erase( it );
					return;
				}
			}
		}
	}
}

void	ProtoIPMgr::incRetryTimes(ProtoIPInfo* info)
{
	ProtoIPInfo* temp = NULL;

	temp = find( info );
	if( temp != NULL )
	{		
		temp->incRetryTimes();
	}
}

void	ProtoIPMgr::clearRetryTimes(ProtoIPInfo* info)
{
	ProtoIPInfo* temp = NULL;

	temp = find( info );
	if( temp != NULL )
	{		
		temp->clearRetryTimes();
	}
}

ProtoIPInfo* ProtoIPMgr::getUsed()
{
	for( std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin(); it != mIPInfos.end(); ++it )
	{
		ProtoIPInfo* temp = *it;
		if( temp == NULL )
			continue;

		if( temp->getUsed() )
			return temp;
	}
	return NULL;
}

ProtoIPInfo* ProtoIPMgr::getUnused()
{
	return getUnused(true);
}

ProtoIPInfo* ProtoIPMgr::getUnused(bool tcp)
{
	ProtoIPInfo* ip = getUnused(tcp, ProtoIPMgr::POLICY_FIRST);
	if( ip != NULL )
		return ip;

	//no way for retry:
	//ip = getUnused(tcp,  ProtoIPMgr::POLICY_FIRST | ProtoIPMgr::POLICY_IGNORE_RETRYTIMES);
	//if( ip != NULL )
	//	return ip;

	ip = getUnused(tcp,  ProtoIPMgr::POLICY_FIRST | POLICY_IGNORE_AREA);
	if( ip != NULL )
		return ip;

	ip = getUnused(tcp,  ProtoIPMgr::POLICY_FIRST | POLICY_IGNORE_AREA | POLICY_IGNORE_ISP);
	if( ip != NULL )
		return ip;

	ip = getUnused(tcp,  ProtoIPMgr::POLICY_FIRST | POLICY_IGNORE_ISP | POLICY_IGNORE_USED);
	if( ip != NULL )
		return ip;

	ip = getUnused(tcp,  ProtoIPMgr::POLICY_FIRST | POLICY_IGNORE_ISP | POLICY_IGNORE_USED | POLICY_IGNORE_GROUP);
	if( ip != NULL )
		return ip;


	return ip;
}

ProtoIPInfo* ProtoIPMgr::getUnused(bool tcp, int policy)
{
	ProtoIPInfo* info = NULL;

	for( std::vector<ProtoIPInfo*>::iterator it = mIPInfos.begin(); it != mIPInfos.end(); ++it )
	{
		ProtoIPInfo* temp = *it;
		if( temp == NULL || temp->isTcp() != tcp )
			continue;

		if( temp->getUsed() )
		{
			if( (policy & ProtoIPMgr::POLICY_IGNORE_USED) != ProtoIPMgr::POLICY_IGNORE_USED )
				continue;
		}
		
		if( mIspType != AUTO_DETECT && temp->getIspType() != mIspType )
		{
			if( (policy & ProtoIPMgr::POLICY_IGNORE_ISP) != ProtoIPMgr::POLICY_IGNORE_ISP )
				continue;
		}

		if( mAreaType != 0 && temp->getAreaType() != mAreaType )
		{
			if( (policy & ProtoIPMgr::POLICY_IGNORE_AREA) != ProtoIPMgr::POLICY_IGNORE_AREA )
				continue;
		}

		if( temp->getRetryTimes() == MAX_IP_RETRY )
		{
			if( (policy & ProtoIPMgr::POLICY_IGNORE_RETRYTIMES) != ProtoIPMgr::POLICY_IGNORE_RETRYTIMES )
				continue;
		}

		//if ip in the same group has been used.
		if( mUsedIPInfos.size() != 0 && temp->getGroup() != 0 )
		{
			bool findGroup = false;
			if( (policy & ProtoIPMgr::POLICY_IGNORE_GROUP) != ProtoIPMgr::POLICY_IGNORE_GROUP )
			{
				for( size_t i=0; i<mUsedIPInfos.size(); i++ )
				{
					if( mUsedIPInfos[i]->getGroup() == temp->getGroup() )
					{
						findGroup = true;
						break;
					}
				}
			}

			if( findGroup )
				continue;
		}
		info = temp;

		//if we want the first meet isp&group, return now:
		if( (policy & ProtoIPMgr::POLICY_FIRST) == ProtoIPMgr::POLICY_FIRST )
			return info;
	}

	return info;
}
