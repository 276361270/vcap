TEMPLATE = lib



DEFINES += _USRDLL
DEFINES += _NOT_INCLUDE_BOOST_BASIC_HEADERS
DEFINES += _NOT_INCLUDE_TOOL_COMMON_HEADERS

CONFIG -= qt

INCLUDEPATH += ../
INCLUDEPATH += ../../include

# Input
HEADERS += 	\
			ProtoConfig.h	\
			ProtoA2U.h		\
			IProtoMod.h	\
			IProtoPacket.h	\
			IProtoLink.h	\
			IProtoTaskThread.h	\
			IProtoPacketPool.h	\
			ProtoHandler.h	\
			ProtoHelper.h	\
			ProtoIPInfo.h	\
			ProtoIPMgr.h	\
			ProtoLgaData.h \
			ProtoLog.h		\
			ProtoMutex.h	\
			ProtoPacketPool.h	\
			AudioPacketPool.h	\
			ProtoTaskThread.h	\
			ProtoTime.h		\
			ProtoUInfo.h		\
			ProtoUtils.h		\
			ProtoSUMap.h		\
			ProtoUList.h		\
			ProtoUSMap.h		\
			ProtoSList.h		\
			ProtoSeqMgr.h		\
			ProtoStatData.h		\
			ProtoNetInit.h		\
			ProtoLink.h			\
			ProtoLinkMgr.h		\
			impl/ProtoLinkMgrImp.h	\
			impl/ProtoUnixLinkImp.h \
			impl/ProtoPacket.h		\
			impl/AudioPacket.h		\
			impl/ProtoMutexImp.h    \
			impl/ProtoPacketPoolImp.h	\
			impl/AudioPacketPoolImp.h	\
			impl/ProtoTaskThreadImp.h	\
			
			
		   

           
SOURCES += 	dllmain.cpp	\
            ProtoA2U.cpp            \
			ProtoHelper.cpp		\
			ProtoIPInfo.cpp		\
			ProtoIPMgr.cpp		\
			ProtoLgaData.cpp    \
			ProtoMutex.cpp		\
			ProtoPacketPool.cpp	\
			AudioPacketPool.cpp	\
			ProtoTaskThread.cpp	\
			ProtoTime.cpp		\
			ProtoUInfo.cpp		\
			ProtoUtils.cpp		\
			ProtoSUMap.cpp		\
			ProtoUList.cpp		\
			ProtoUSMap.cpp		\
			ProtoSList.cpp		\
			ProtoSeqMgr.cpp		\
			ProtoStatData.cpp	\
			ProtoNetInit.cpp	\
			ProtoLink.cpp		\
			ProtoLinkMgr.cpp	\
			impl/ProtoLinkMgrImp.cpp	\
			impl/ProtoUnixLinkImp.cpp   \
			impl/ProtoPacket.cpp	\
			impl/AudioPacket.cpp	\
			impl/ProtoMutexImp.cpp  \
			impl/ProtoPacketPoolImp.cpp	\
			impl/AudioPacketPoolImp.cpp	\
			impl/ProtoTaskThreadImp.cpp	\
			impl/ProtoStatDataImp.cpp	\
			


win32 {
PRECOMPILED_HEADER = stdafx.h
include(../../include/common.pri)

#LIBS += netio.lib
LIBS += netmod.lib
LIBS += ws2_32.lib
LIBS += Winmm.lib


CONFIG += rtti
QMAKE_CXXFLAGS += /EHsc

INCLUDEPATH += ../../../depends/dw3rd/zlib-1.2.5/include
QMAKE_LIBDIR += ../../../depends/dw3rd/zlib-1.2.5/lib/release

QMAKE_LFLAGS_RELEASE += /BASE:0x45100000

HEADERS +=              \


SOURCES +=             impl/ProtoWinThread.cpp	\


}


unix {
DESTDIR = ../../../bin/

LIBS += -lz
}
