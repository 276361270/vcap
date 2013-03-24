TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

# Input
HEADERS += dsxconfig.h
HEADERS += dsxfilter.h
HEADERS += x264transform.h


SOURCES += dllmain.cpp
SOURCES += dsxfilter.cpp
SOURCES += x264transform.cpp

DEF_FILE = x264filter.def



INCLUDEPATH += ../baseclasses

LIBS += baseclasses.lib
LIBS += libx264-130.lib
LIBS += Strmiids.lib
LIBS += winmm.lib
