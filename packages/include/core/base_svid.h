#ifndef BASE_SVID_H
#define BASE_SVID_H
#include <string>

namespace protocol{


enum svid {
	SVID_SMGR		= 0,
	SVID_SMP		= 1,
	SVID_LOGIN		= 2,	
	SVID_UINFO		= 3,
	SVID_FRIENDS	= 4,

	SVID_SESSION	= 5,
	SVID_IM			= 6,
};



}
#endif /*BASE_SVID_H_*/
