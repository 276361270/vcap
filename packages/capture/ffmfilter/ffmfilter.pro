TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

# Input
HEADERS += ffmconfig.h
HEADERS += ffmfilter.h
HEADERS += ffmtransform.h
HEADERS += ffmfilestream.h


SOURCES += dllmain.cpp
SOURCES += ffmfilter.cpp
SOURCES += ffmtransform.cpp
SOURCES += ffmfilestream.cpp

DEF_FILE = ffmfilter.def



INCLUDEPATH += ../baseclasses

LIBS += baseclasses.lib
LIBS += avutil.lib
LIBS += avformat.lib
LIBS += avcodec.lib
LIBS += Strmiids.lib
LIBS += winmm.lib
