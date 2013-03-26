#ifndef _PROTO_LGA_DATA_H_
#define _PROTO_LGA_DATA_H_
#include "ProtoConfig.h"

class SESSCOMM_API ProtoLgaData
{
private:
    ProtoLgaData();
    ~ProtoLgaData(){}

public:
    static ProtoLgaData* Instance();

public:
	inline void setUid(uint32_t uid)					 { m_uUid = uid; }
    inline void setAnonymous(bool bAnonymous)            { m_bAnonymous = bAnonymous; }
    inline void setReconnect(bool bIsReConnect)          { m_bReconnect = bIsReConnect; }
    inline void setSavePsw(bool bSave)                   { m_bSavePwd = bSave; }
    inline void setEmailLogin(bool bEmail)               { m_bEmailLogin = bEmail; }

    inline void setIspType(ISPType type)                 { m_ispType = type; }
    inline void setTestIsp(ISPType type)                 { m_testIsp = type; }
    inline void setAutoTestIsp(ISPType type)             { m_autoTestIsp = type; }
    inline void setClientIsp(ISPType type)               { m_clientIsp = type; }
    inline void setAreaType(AreaType type)               { m_areaType = type; }

    inline void setCodeID(uint32_t codeID)               { m_uCodeID = codeID; }
    inline void setLbsTime(uint32_t time)                { m_uLbsTime = time; }
    inline void setLinkdTime(uint32_t time)              { m_uLinkdTime = time; }
    inline void setLoginTime(uint32_t time)              { m_uLoginTime = time; }
    inline void setProtoVer(uint32_t version)            { m_uProtoVer = version; }    
    inline void setWANIp(uint32_t WAN_Ip)                { m_uWANIp = WAN_Ip; }

    inline void setAccount(std::string account)         { m_strAccount = account; }
    inline void setBanNote(std::string note)            { m_strBanNote = note; }
    inline void setCodeData(std::string code)           { m_strCodeData = code; }
    inline void setLbsTestAddr(std::string addr)        { m_strLbsAutoTestAddr = addr; }
    inline void setLbsShutdownMsg(std::string msg)      { m_strLbsShutdownMsg = msg; }
    inline void setModVerInfo(std::string verInfo)      { m_strModVerInfo = verInfo; }
    inline void setClientVer(std::string version)       { m_strClientVer = version; }
    inline void setPassport(std::string passport)       { m_strPassport = passport; }
    inline void setShaPasswd(std::string ShaPwd)        { m_strShaPwd = ShaPwd; }
    inline void setUnBanDate(std::string date)          { m_strUnBanDate = date; }
    inline void setCookie(std::string cookie)           { m_strCookie = cookie; }

public:
	inline uint32_t    getUid()				{ return m_uUid; }
    inline bool        isAnonymous()        { return m_bAnonymous; }
    inline bool        isReconnect()        { return m_bReconnect; }
    inline bool        isSavePsw()          { return m_bSavePwd; }
    inline bool        isEmailLogin()       { return m_bEmailLogin; }

    inline ISPType     getIspType()         { return m_ispType; }
    inline ISPType     getTestIsp()         { return m_testIsp; }
    inline ISPType     getAutoTestIsp()     { return m_autoTestIsp; }
    inline ISPType     getClientIsp()       { return m_clientIsp; }
    inline AreaType    getAreaType()        { return m_areaType; }

    inline uint32_t    getCodeID()          { return m_uCodeID; }
    inline uint32_t    getLbsTime()         { return m_uLbsTime; }
    inline uint32_t    getLinkdTime()       { return m_uLinkdTime; }
    inline uint32_t    getLoginTime()       { return m_uLoginTime; }
    inline uint32_t    getProtoVer()        { return m_uProtoVer; }    
    inline uint32_t    getWANIp()           { return m_uWANIp; }

    inline std::string& getAccount()        { return m_strAccount; }
    inline std::string& getBanNote()        { return m_strBanNote; }
    inline std::string& getCodeData()       { return m_strCodeData; }
    inline std::string& getLbsTestAddr()    { return m_strLbsAutoTestAddr; }
    inline std::string& getLbsShutdownMsg() { return m_strLbsShutdownMsg; }
    inline std::string& getModVerInfo()     { return m_strModVerInfo; }
    inline std::string& getClientVer()      { return m_strClientVer; }
    inline std::string& getPassport()       { return m_strPassport; }
    inline std::string& getShaPasswd()      { return m_strShaPwd; }
    inline std::string& getUnBanDate()      { return m_strUnBanDate; }
    inline std::string& getCookie()         { return m_strCookie; }

private:
	uint32_t                m_uUid;
    bool                    m_bAnonymous;
    bool                    m_bReconnect;
    bool                    m_bSavePwd;
    bool                    m_bEmailLogin;
    ISPType                 m_ispType;
    ISPType                 m_testIsp; //测速最快的那个ISP
    ISPType                 m_autoTestIsp; //自动化测试设置的测试ISP
    ISPType                 m_clientIsp;  //登陆的那个LBS返回的客户端isp
    AreaType                m_areaType;
    uint32_t                m_uCodeID;    
    uint32_t                m_uProtoVer;
    uint32_t                m_uWANIp;
    uint32_t                m_uLbsTime;
    uint32_t                m_uLinkdTime;
    uint32_t                m_uLoginTime;
    std::string             m_strAccount;
    std::string             m_strBanNote;
    std::string             m_strCookie;
    std::string             m_strCodeData;
    std::string             m_strClientVer;
    std::string             m_strLbsAutoTestAddr; //自动化测试设置的LBS测试地址
    std::string             m_strLbsShutdownMsg;
    std::string             m_strModVerInfo;
    std::string             m_strPassport;
    std::string             m_strShaPwd;
    std::string             m_strUnBanDate;
    static ProtoLgaData*    m_pInstance;
};

#endif


