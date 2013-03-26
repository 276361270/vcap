TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

# Input
HEADERS += spxconfig.h
HEADERS += spxfilter.h
HEADERS += spxtransform.h


SOURCES += dllmain.cpp
SOURCES += spxfilter.cpp
SOURCES += spxtransform.cpp

DEF_FILE = spxfilter.def



INCLUDEPATH += ../baseclasses

LIBS += baseclasses.lib
LIBS += libspeex.lib
LIBS += Strmiids.lib
LIBS += winmm.lib
