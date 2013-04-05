TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

INCLUDEPATH += ./
INCLUDEPATH += ../../include
INCLUDEPATH += ../libspeex/include

# Input
HEADERS += 	\
        vcapconfig.h        \
        dspin.h             \
        engine.h			\
        dsfilter.h			\
        camera.h			\
        camerafactory.h		\
        vmrrender.h			\
        filefilter.h		\
        mic.h				\
        micfactory.h		\
        ffmencoder.h		\
        livecapture.h		\
        audiocapture.h      \
        videocapture.h      \
        
            

           
SOURCES += 	\
        dspin.cpp           \
        engine.cpp          \
        dsfilter.cpp        \
        dllmain.cpp			\
        camera.cpp			\
        camerafactory.cpp	\
        vmrrender.cpp		\
        filefilter.cpp		\
        mic.cpp				\
        micfactory.cpp		\
        ffmencoder.cpp		\
        livecapture.cpp		\
        audiocapture.cpp    \
        videocapture.cpp    \
            
            
            
