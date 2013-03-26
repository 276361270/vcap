#include "ProtoUInfo.h"

ProtoUInfo::ProtoUInfo()
{
	reset();
}

uint32_t	ProtoUInfo::getUid()
{
	return mUInfo.uid;
}
	
std::string ProtoUInfo::getNick()
{
	if( mUInfo.nick.length() != 0 )
		return mUInfo.nick;
	
	return "";
}

std::string ProtoUInfo::getSign()
{
	return mUInfo.sign;
}

std::string ProtoUInfo::getIntro()
{
	return mUInfo.intro;
}

int			ProtoUInfo::getGender()
{
	return mUInfo.gender;
}

uint32_t	ProtoUInfo::getBirthday()
{
	return mUInfo.birthday;
}

int			ProtoUInfo::getArea()
{
	return mUInfo.area;
}

int			ProtoUInfo::getProvince()
{
	return mUInfo.province;
}

int			ProtoUInfo::getCity()
{
	return mUInfo.city;
}

bool		ProtoUInfo::getValidate()
{
	return mUInfo.validate;
}

uint32_t	ProtoUInfo::getUpdateTime()
{
	return mUInfo.updateTime;
}

uint32_t	ProtoUInfo::getUpdateIp()
{
	return mUInfo.updateIp;
}

uint32_t	ProtoUInfo::getJifen()
{
	return mUInfo.jifen;
}

uint32_t    ProtoUInfo::getLoginStamp()
{
    return mUInfo.loginStamp;
}

void	ProtoUInfo::setUid(uint32_t uid)
{
	mUInfo.uid = uid;
}

void	ProtoUInfo::setNick(std::string nick)
{
	mUInfo.nick = nick;
}

void	ProtoUInfo::setSign(std::string sign)
{
	mUInfo.sign = sign;
}

void	ProtoUInfo::setIntro(std::string intro)
{
	mUInfo.intro = intro;
}

void	ProtoUInfo::setGender(int gender)
{
	mUInfo.gender = gender;
}

void	ProtoUInfo::setBirthday(uint32_t birthday)
{
	mUInfo.birthday = birthday;
}

void	ProtoUInfo::setArea(int area)
{
	mUInfo.area = area;
}

void	ProtoUInfo::setProvince(int province)
{
	mUInfo.province = province;
}

void	ProtoUInfo::setCity(int city)
{
	mUInfo.city = city;
}

void	ProtoUInfo::setValidate(bool validate)
{
	mUInfo.validate = validate;
}

void	ProtoUInfo::setUpdateTime(uint32_t time)
{
	mUInfo.updateTime = time;
}

void	ProtoUInfo::setUpdateIp(uint32_t ip)
{
	mUInfo.updateIp = ip;
}

void	ProtoUInfo::setJifen(uint32_t jifen)
{
	mUInfo.jifen = jifen;
}

void    ProtoUInfo::setLoginStamp(uint32_t loginStamp)
{
    mUInfo.loginStamp = loginStamp;
}

void	ProtoUInfo::reset()
{
	mUInfo.uid = 0;
	mUInfo.gender = 0;
	mUInfo.birthday = 19900101;
	mUInfo.area = 0;
	mUInfo.province = 0;
	mUInfo.city = 0;
	mUInfo.validate = false;
	mUInfo.updateTime = 0;
	mUInfo.updateIp = 0;
	mUInfo.jifen = 0;
	mUInfo.loginStamp = 0;
}