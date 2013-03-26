#ifndef	ProtoUInfo_H
#define ProtoUInfo_H

#include "ProtoConfig.h"
#include <string>
#include <vector>

class SESSCOMM_API ProtoUInfo
{
public:
	struct UInfo
	{
		uint32_t	uid;
		std::string nick;
		std::string sign;
		std::string intro;
		int			gender;
		uint32_t	birthday;
		int			area;
		int			province;
		int			city;
		bool		validate;
		std::string resume;
		uint32_t	updateTime;
		uint32_t	updateIp;
		uint32_t	jifen;	
        uint32_t    loginStamp;
	};

public:
	ProtoUInfo();

public:
	uint32_t	getUid();
	std::string getNick();
	std::string getSign();
	std::string getIntro();
	int			getGender();
	int			getIspType();
	int			getAreaType();
    uint32_t    getWANIp();
	uint32_t	getBirthday();
	int			getArea();
	int			getProvince();
	int			getCity();
	bool		getValidate();
	uint32_t	getUpdateTime();
	uint32_t	getUpdateIp();
	uint32_t	getJifen();
    uint32_t    getLoginStamp();

	void	setUid(uint32_t uid);
	void	setNick(std::string nick);
	void	setSign(std::string sign);
	void	setIntro(std::string intro);
	void	setGender(int gender);
	void	setIspType(int isp);
	void	setAreaType(int area);
    void    setWANIp(uint32_t ip);
	void	setBirthday(uint32_t birthday);
	void	setArea(int area);
	void	setProvince(int province);
	void	setCity(int city);
	void	setValidate(bool validate);
	void	setUpdateTime(uint32_t time);
	void	setUpdateIp(uint32_t ip);
	void	setJifen(uint32_t jifen);
    void    setLoginStamp(uint32_t loginStamp);
	void	reset();

private:
	UInfo	mUInfo;
};

#endif
