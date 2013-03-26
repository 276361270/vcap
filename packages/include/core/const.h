#ifndef CROSS_PLANTFORM_CONST_H_
#define CROSS_PLANTFORM_CONST_H_

#define LBS_SERVER_PORT1 1001
#define LBS_SERVER_PORT2 2001
#define LBS_SERVER_PORT3 3001
#define LBS_SERVER_PORT80 80


#define MAX_SVID_NUM 20
#define SOCKET_TIMEOUT 60000
#define MYCOLLECTION_FOLDER 1000000000
#define PUBLICCHANNEL_FOLDER 1000000001
#define RECEMMONDCHANNEL_FOLDER 1000000002
#define HOT_FOLDER 1000000003
#define UDP_OFFSET 10000
#define INVALID_UID 0xffffffff
#define INVALID_CID 0xffffffff
#define NONE_SERVER_ID 0xffffffff

#define MAX_CHANNEL_SIZE 3
#ifdef WIN32
#define FAV_FOLDER		_T("1000000000")
#define FAV_PUBLIC		_T("1000000001")
#define FAV_RECOMMEND	_T("1000000002")
#define FAV_HOT			_T("1000000003")
#define KICKOUT_PID _T("")
#endif

#define SEQPAGE					1000
#define SEQORIGINAL				1000

#define DEF_SESSIONKEY_LENGTH 16

#define ADMIN_CHANNEL 0

#define NO_IMID -1

namespace protocol{
	enum E_ONLINESTAT{ONLINE, OFFLINE};
	enum E_IMSTATUS
	{
		IMONLINE, 
		IMHIDE, 
		IMOFFLINE,
		ENUM_IMSTATUS_BUSY,    //  在protocol中提前做好兼容，对UI来说 等同于在线
		ENUM_IMSTATUS_LEAVE,   //  方便后续忙碌、离开等状态的扩展
		ENUM_IMSTATUS_GAMING   //  游戏中
	};
}

#define ISONLINE(imState) (((imState) == protocol::IMOFFLINE || (imState) == protocol::IMHIDE) ? false : true)

namespace protocol {
namespace uinfo {
enum SEX {
	female = 0,
	male,
	unknown
};

}
}

enum ISPType{
	AUTO_DETECT = 0,
	CTL = 1,	//电信
	CNC = 2,	//网通
	CNII = 4,	//铁通
	EDU = 8,	//教育网
	WBN	= 16,	//长城宽带

	GENERAL_DEPLOY = 3,	// general session, main deploy type
	SIFU_DEPLOY = 45,		
	PIP_DEPLOY = 46,
	IM_DEPLOY = 47,
	MAFIA_DEPLOY = 48,
};

enum AreaType{//同网络类型的定义数字必需连续(分配的时候会用)
	AREA_UNKNOWN = 0,
	CTL_EAST = 16,  //电信东区     10000  (1<<4) + 0
	CTL_WEST = 17,  //电信西区     10001  (1<<4) + 1
	CNC_NE = 32,    //网通东北    100000 (2<<4) + 0
	CNC_NC = 33,    //网通华北    100001 (2<<4) + 1
	CNII_AREA = 64, //铁通       1000000 (4<<4) + 1
	EDU_AREA = 128, //教育网    10000000 (8<<4) +0
	WBN_AREA = 256,          //长城宽带 100000000 (16<<4) +0
	MOB_AREA = 512, //移动    1000000000 (32<<4) + 0

};

enum ChannelDeploy {
	UNKNOWN_SESSION = 0,
	GENERAL_SESSION = 3,	// general session, main deploy type
	SIFU_SESSION = 45,		
	PIP_SESSION = 46,
	IM_SESSION = 47,
	MAFIA_SESSION = 48,
};
enum KickType{
	KICKOUT_CHANNEL,
	LOGIN_FREEZED
};

namespace protocol
{
namespace sysmsg
{
	enum SysMsgDisplayType
	{
		//10秒后自动关闭系统消息窗口
		ENUM_SYSMSG_AUTO_CLOSE = 0,
		//用户手动关闭
		ENUM_SYSMSG_USER_CLOSE,

		ENUM_SYSMSG_PRIVILEDGE,
		//邮箱密保
		ENUM_SYSMSG_MAILCHANGE,

		//频道活动提醒
		ENUM_SYSMSG_ACTIVITY,
		//YYBanner消息
		ENUM_YYBANNER = 5 ,
		//新消息消息类型
		ENUM_COMMON_SYSTEMMSG = 100,
		//麦序提醒消息
		ENUM_SYSMSG_MICNOTIFY,
		//帮带系统通知消息
		ENUM_BANGDAI_INFORMMSG,
		//安全等级
		ENUM_SYSMSG_SAFEACCT = 103
	};
}
namespace uinfo{
	enum ApplyResult{
		APPLY_SUCCESS,
		NOT_ENOUGH_JIFEN,
		IN_QUIT_COOLDOWN,
		EXCEED_MAX_APPLYCOUNT,
		ALREADY_MEMBER,
		WAITFOR_APPROVE
	};

	enum InviteCodeApplyResult
	{
		CODE_APPLY_SUCCESS,
		CODE_OUT_OF_DATE, //邀请码过期
		CODE_HAVE_USED,   //邀请码已经使用
		CODE_HANDIN_FALSE, //邀请码提交失败
		CODE_ERROR         //邀请码错误
	};
}
}

namespace protocol
{
namespace p2p
{
	#define LAN_BLOCK_SIZE			    (8*1024)//8KB
	#define WAN_BLOCK_SIZE				(1024)//(1300)
	#define BRIDGE_BLOCK_SIZE			(1024)//1 KBytes
	#define LINKD_BLOCK_SIZE			(1024)//1 KBytes

	#define MAX_P2P_TORRENT_CELL_CNT	(64)
	#define MAX_P2P_TORRENT_CELL_SIZE	(1024)
 	#define MAX_P2P_TORRENT_SEED_SIZE	(MAX_P2P_TORRENT_CELL_CNT*MAX_P2P_TORRENT_CELL_SIZE) //64KB
	#define MAX_MX_BASIC_FILE_SIZE		(1*1024*1024)//1MB

	#define INVALID_P2P_FILE_SIZE		(0xffffffffffffffff)
	#define INVALID_P2P_FILES_CNT		(0xffffffff)
	#define INVALID_P2P_FILE_HANDLE 	(0xffffffff)
	#define INVALID_P2P_CHAN_NUM		(0xffff)
	#define MX_TT_CHAN_NUM				(INVALID_P2P_CHAN_NUM-1)

	#define ASYNC_PACKET_ID				(0xffffffff)

	//torrent task state.
	#define TORRENT_TASK_STATE_NOTCOMMIT		(0)
	#define TORRENT_TASK_STATE_COMMITTED		(1)

	//torrent file state.
	#define TORRENT_FILE_STATE_UNREADY		(0)
	#define TORRENT_FILE_STATE_OPENING		(1)
	#define TORRENT_FILE_STATE_READY 		(2)

	//TODO: up2p
	enum P2PTransmitAction
	{
		ENUM_P2P_ACTION_ACCEPT = 0,	//对方已接受
		ENUM_P2P_ACTION_REFUSE,		//对方已拒绝
		ENUM_P2P_ACTION_VIDEOING,	//视频进行中
		ENUM_P2P_ACTION_START_CAMERA,//通知本方视频数据可以开始采集
		ENUM_P2P_ACTION_STOP_CAMERA, //通知奔放视频数据需要停止采集
		ENUM_P2P_ACTION_NOT_SUPPORT = 0xff      //对方版本不支持
	};


	/**
	 * Special note:
	 * 	1: 1V1 video is an open control and single best case. 
	 *    At the first accept action, app will use task ready to update channel ready information, in case accept from message box.
	 *    Because biz not ready to save the ready channel information as channel ready from chan preconn.
	 *  2:
	 **/
	enum P2PTransmitStatus
	{	
		ENUM_P2P_TRANSMIT_CHAN_WAITING = 0,		//正在建立连接
		ENUM_P2P_TRANSMIT_READY,			//双方连接已建立，开始传输
		ENUM_P2P_TRANSMIT_FINISH,			//传输完成
		ENUM_P2P_TRANSMIT_IO_ERROR,			//文件系统错误			
		ENUM_P2P_TRANSMIT_NETWORK_ERROR,	//传输出现错误，任务已中断
		ENUM_P2P_TRANSMIT_FAILED,			//连接建立失败
		ENUM_P2P_TRANSMIT_CANCEL,
		ENUM_P2P_TRANSMIT_PCONN_READY,		//预连接建立已建立.
		ENUM_P2P_TRANSMIT_PCONN_NOTREADY,	//预连接未建立.
		ENUM_P2P_TRANSMIT_DRIVER_ERROR,		//文件盘符异常.
		ENUM_P2P_TRANSMIT_TTL_WARN,			//发送队列杜塞严重.
		ENUM_P2P_TRANSMIT_BANDWIDTH,		//传输带宽通知.
		ENUM_P2P_TRANSMIT_PUNCH_READY,      //打洞连接建立
		ENUM_P2P_TRANSMIT_SERVER_READY,     //服务器中转连接建立
		ENUM_P2P_TRANSMIT_SPEED_MONITOR,    //链路测试结果.
		ENUM_P2P_TRANSMIT_SERVER_CONN_RES,  //服务器备用链路(通道1,2)建立请求的响应.
		ENUM_P2P_TRANSMIT_NEW_MAINCHAN,		//通道切换主链路更新通知.

		ENUM_P2P_TRANSMIT_CHAN_READY,		//某传输通道已建立成功.

		ENUM_P2PVIDEO_CAMERA_IN = 50,
		ENUM_P2PVIDEO_CAMERA_OUT,
		ENUM_P2PVIDEO_RES_UPDATE,
		ENUM_P2PVIDEO_RES_PEER_UP,
		ENUM_P2PVIDEO_RES_PEER_DN,

		ENUM_P2P_TRANSMIT_UNKNOW = 0xff
	};

	enum P2PVideoCameraStatus
	{
		ENUM_IMP2PVIDEO_CAMERA_IN,
		ENUM_IMP2PVIDEO_CAMERA_OUT,
		ENUM_IMP2PVIDEO_RESOLUTION_CHANGE,
		ENUM_IMP2PVIDEO_RESOLUTION_CHANGE_UP_PEER,
		ENUM_IMP2PVIDEO_RESOLUTION_CHANGE_DOWN_PEER,
		ENUM_IMP2PVIDEO_TTL_CHANGE, //TODO:up2p

		ENUM_IMP2PVIDEO_UNKNOWN = 0xff
	};

	enum eExternReason
	{
		E_P2P_REASON_USER = 0,
		E_P2P_REASON_NORES,
		E_P2P_REASON_AUTO,
		E_P2P_REASON_ONLY_ONE_INSTANCE,
	
		E_P2P_REASON_UNKNOWN = 0xff
	};

	enum P2PNatType
	{
		ENUM_P2P_NAT_UNKNOWN = 0,
		ENUM_P2P_NAT_OPEN_INTERNET,
		ENUM_P2P_NAT_FULL_CONE,
		ENUM_P2P_NAT_RESTRICT_CONE,
		ENUM_P2P_NAT_UDP_FIREWALL,
		ENUM_P2P_NAT_SYMMETRIC,
		ENUM_P2P_NAT_UDP_BLOCK,
		EMUN_P2P_NAT_SAME_LAN,
	};

	enum E_P2P_MYROLE
	{
		E_P2P_SENDER = 0,
		E_P2P_RECEIVER
	};
	
	enum E_P2P_METHOD
	{
		E_P2P_UDP = 0,
		E_P2P_TCP,
		E_P2P_UDT,

		E_P2P_METHOD_UNKNOWN = 0xff
	};

	enum E_P2P_FUNC
	{
		E_P2P_FUNC_BRIDGE =0 ,
		E_P2P_FUNC_LINKD,
		E_P2P_FUNC_UDT,
		E_P2P_FUNC_MX,
		E_P2P_FUNC_UDT_SERVER,
		E_P2P_FUNC_VIDEO_BEST,
		E_P2P_FUNC_UNION,//p2p data transmit union chan.

		E_P2P_FUNC_INVALID = 0xff
		
	};

	enum eP2PNetioTimerid
	{
		E_UTIMERID_HS_RETRY = 0,
		E_UTIMERID_CONN_CHECK = 1,
		E_UTIMERID_RUDP_RETRY = 2,

		E_UTIMERID_INVALID = 0xff
	};

	enum eChanMethod
	{
		E_CHAN_METHOD_XAN = 0,
		E_CHAN_METHOD_BRIDGE,
		E_CHAN_METHOD_LINKD,

		E_CHAN_METHOD_UNKNOWN = 0xff			
	};

}
}

namespace protocol
{
namespace session
{
	enum SyncRoleReason
	{
		INVITE_CODE = 1
	};
}
}

namespace protocol {
	namespace imvip {

		enum E_VIP_RING_TYPE {
			E_RING_NULL = 0,
			E_RING_LITERAL,
			E_RING_VOICE
		};
	}
}

#endif /*CROSS_PLANTFORM_CONST_H_*/
