TEMPLATE = lib

include(../../include/common.pri)

CONFIG -= qt

INCLUDEPATH += ./
INCLUDEPATH += ../../include
INCLUDEPATH += ../libspeex/include

LIBS += libspeex.lib

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
        vcapvideoencoder.h		\
        vcapvideoencoderfactory.h	\
        vcapvmrrender.h			\
        vcapfilefilter.h		\
        vcapaudioencoder.h		\
        vcapaudioencoderfactory.h\
        vcapmic.h				\
        vcapmicfactory.h		\
        vcapsamplegrabber.h		\
        vcaplivecapture.h		\
        vcapspxencfilter.h		\
        
            

           
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
        vcapvideoencoder.cpp	\
        vcapvideoencoderfactory.cpp	\
        vcapvmrrender.cpp		\
        vcapfilefilter.cpp		\
        vcapaudioencoder.cpp	\
        vcapaudioencoderfactory.cpp	\
        vcapmic.cpp				\
        vcapmicfactory.cpp		\
        vcapsamplegrabber.cpp	\
        vcaplivecapture.cpp		\
        vcapspxencfilter.cpp	\
            
            
            
