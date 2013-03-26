CONFIG += accessible
DEFINES += DUI_ACCESSIBLE

win32{
include(buildoption.pri)

QMAKE_LIBDIR += "$(TargetDir)"
QMAKE_LIBDIR += "$(TargetDir)/../"
CONFIG(debug, debug)
{
    DESTDIR = ../../../bin/debug
}

CONFIG(release, release)
{
    DESTDIR = ../../../bin/release
}
}#win32

INCLUDEPATH += .
INCLUDEPATH += ../../include
INCLUDEPATH += ../../../bin/include
INCLUDEPATH += ../../../depends/ffmpeg/include

QMAKE_LIBDIR += ../../../depends/ffmpeg/lib
