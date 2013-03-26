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
		ENUM_IMSTATUS_BUSY,    //  ��protocol����ǰ���ü��ݣ���UI��˵ ��ͬ������
		ENUM_IMSTATUS_LEAVE,   //  �������æµ���뿪��״̬����չ
		ENUM_IMSTATUS_GAMING   //  ��Ϸ��
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
	CTL = 1,	//����
	CNC = 2,	//��ͨ
	CNII = 4,	//��ͨ
	EDU = 8,	//������
	WBN	= 16,	//���ǿ��

	GENERAL_DEPLOY = 3,	// general session, main deploy type
	SIFU_DEPLOY = 45,		
	PIP_DEPLOY = 46,
	IM_DEPLOY = 47,
	MAFIA_DEPLOY = 48,
};

enum AreaType{//ͬ�������͵Ķ������ֱ�������(�����ʱ�����)
	AREA_UNKNOWN = 0,
	CTL_EAST = 16,  //���Ŷ���     10000  (1<<4) + 0
	CTL_WEST = 17,  //��������     10001  (1<<4) + 1
	CNC_NE = 32,    //��ͨ����    100000 (2<<4) + 0
	CNC_NC = 33,    //��ͨ����    100001 (2<<4) + 1
	CNII_AREA = 64, //��ͨ       1000000 (4<<4) + 1
	EDU_AREA = 128, //������    10000000 (8<<4) +0
	WBN_AREA = 256,          //���ǿ�� 100000000 (16<<4) +0
	MOB_AREA = 512, //�ƶ�    1000000000 (32<<4) + 0

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
		//10����Զ��ر�ϵͳ��Ϣ����
		ENUM_SYSMSG_AUTO_CLOSE = 0,
		//�û��ֶ��ر�
		ENUM_SYSMSG_USER_CLOSE,

		ENUM_SYSMSG_PRIVILEDGE,
		//�����ܱ�
		ENUM_SYSMSG_MAILCHANGE,

		//Ƶ�������
		ENUM_SYSMSG_ACTIVITY,
		//YYBanner��Ϣ
		ENUM_YYBANNER = 5 ,
		//����Ϣ��Ϣ����
		ENUM_COMMON_SYSTEMMSG = 100,
		//����������Ϣ
		ENUM_SYSMSG_MICNOTIFY,
		//���ϵͳ֪ͨ��Ϣ
		ENUM_BANGDAI_INFORMMSG,
		//��ȫ�ȼ�
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
		CODE_OUT_OF_DATE, //���������
		CODE_HAVE_USED,   //�������Ѿ�ʹ��
		CODE_HANDIN_FALSE, //�������ύʧ��
		CODE_ERROR         //���������
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
		ENUM_P2P_ACTION_ACCEPT = 0,	//�Է��ѽ���
		ENUM_P2P_ACTION_REFUSE,		//�Է��Ѿܾ�
		ENUM_P2P_ACTION_VIDEOING,	//��Ƶ������
		ENUM_P2P_ACTION_START_CAMERA,//֪ͨ������Ƶ���ݿ��Կ�ʼ�ɼ�
		ENUM_P2P_ACTION_STOP_CAMERA, //֪ͨ������Ƶ������Ҫֹͣ�ɼ�
		ENUM_P2P_ACTION_NOT_SUPPORT = 0xff      //�Է��汾��֧��
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
		ENUM_P2P_TRANSMIT_CHAN_WAITING = 0,		//���ڽ�������
		ENUM_P2P_TRANSMIT_READY,			//˫�������ѽ�������ʼ����
		ENUM_P2P_TRANSMIT_FINISH,			//�������
		ENUM_P2P_TRANSMIT_IO_ERROR,			//�ļ�ϵͳ����			
		ENUM_P2P_TRANSMIT_NETWORK_ERROR,	//������ִ����������ж�
		ENUM_P2P_TRANSMIT_FAILED,			//���ӽ���ʧ��
		ENUM_P2P_TRANSMIT_CANCEL,
		ENUM_P2P_TRANSMIT_PCONN_READY,		//Ԥ���ӽ����ѽ���.
		ENUM_P2P_TRANSMIT_PCONN_NOTREADY,	//Ԥ����δ����.
		ENUM_P2P_TRANSMIT_DRIVER_ERROR,		//�ļ��̷��쳣.
		ENUM_P2P_TRANSMIT_TTL_WARN,			//���Ͷ��ж�������.
		ENUM_P2P_TRANSMIT_BANDWIDTH,		//�������֪ͨ.
		ENUM_P2P_TRANSMIT_PUNCH_READY,      //�����ӽ���
		ENUM_P2P_TRANSMIT_SERVER_READY,     //��������ת���ӽ���
		ENUM_P2P_TRANSMIT_SPEED_MONITOR,    //��·���Խ��.
		ENUM_P2P_TRANSMIT_SERVER_CONN_RES,  //������������·(ͨ��1,2)�����������Ӧ.
		ENUM_P2P_TRANSMIT_NEW_MAINCHAN,		//ͨ���л�����·����֪ͨ.

		ENUM_P2P_TRANSMIT_CHAN_READY,		//ĳ����ͨ���ѽ����ɹ�.

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
