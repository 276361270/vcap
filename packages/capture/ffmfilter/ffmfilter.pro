TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

# Input
HEADERS += ffmconfig.h
HEADERS += ffmfilter.h
HEADERS += ffmtransform.h
HEADERS += ffmlog.h
HEADERS += ffmaachandler.h
HEADERS += ffmh264handler.h
HEADERS += ffmutil.h
HEADERS += ffmoutformat.h


SOURCES += dllmain.cpp
SOURCES += ffmfilter.cpp
SOURCES += ffmtransform.cpp
SOURCES += ffmaachandler.cpp
SOURCES += ffmh264handler.cpp
SOURCES += ffmoutformat.cpp

DEF_FILE = ffmfilter.def



INCLUDEPATH += ../baseclasses

LIBS += baseclasses.lib
LIBS += avutil.lib
LIBS += avformat.lib
LIBS += avcodec.lib
LIBS += swscale.lib
LIBS += Strmiids.lib
LIBS += winmm.lib
