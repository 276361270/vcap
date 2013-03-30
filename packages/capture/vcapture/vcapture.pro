TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

INCLUDEPATH += ./
INCLUDEPATH += ../../include
INCLUDEPATH += ../libspeex/include

# Input
HEADERS += 	\
        vcapconfig.h            \
        vcappin.h               \
        vcapengine.h			\
        vcapenginefactory.h		\
        vcapfilter.h			\
        vcapcamera.h			\
        camerafactory.h			\
        vcapvmrrender.h			\
        vcapfilefilter.h		\
        vcapmic.h				\
        vcapmicfactory.h		\
        ffmencoder.h			\
        livecapture.h			\
        audiocapture.h      	\
        videocapture.h      	\
        
            

           
SOURCES += 	\
        vcappin.cpp             \
        vcapengine.cpp          \
        vcapenginefactory.cpp	\
        vcapfilter.cpp          \
        dllmain.cpp				\
        vcapcamera.cpp			\
        camerafactory.cpp		\
        vcapvmrrender.cpp		\
        vcapfilefilter.cpp		\
        vcapmic.cpp				\
        vcapmicfactory.cpp		\
        ffmencoder.cpp			\
        livecapture.cpp			\
        audiocapture.cpp    	\
        videocapture.cpp    	\
            
            
            
