TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

INCLUDEPATH += ./
INCLUDEPATH += ../../include
INCLUDEPATH += ../libspeex/include

# Input
HEADERS += 	\
        vcapaudiocapture.h      \
        vcapconfig.h            \
        vcappin.h               \
        vcapvideocapture.h      \
        vcapengine.h			\
        vcapenginefactory.h		\
        vcapfilter.h			\
        vcapcamera.h			\
        vcapcamerafactory.h		\
        vcapvmrrender.h			\
        vcapfilefilter.h		\
        vcapmic.h				\
        vcapmicfactory.h		\
        vcapsamplegrabber.h		\
        vcaplivecapture.h		\
        ffmencoder.h			\
        
            

           
SOURCES += 	\
        vcapaudiocapture.cpp    \
        vcappin.cpp             \
        vcapvideocapture.cpp    \
        vcapengine.cpp          \
        vcapenginefactory.cpp	\
        vcapfilter.cpp          \
        dllmain.cpp				\
        vcapcamera.cpp			\
        vcapcamerafactory.cpp	\
        vcapvmrrender.cpp		\
        vcapfilefilter.cpp		\
        vcapmic.cpp				\
        vcapmicfactory.cpp		\
        vcapsamplegrabber.cpp	\
        vcaplivecapture.cpp		\
        ffmencoder.cpp			\
            
            
            
