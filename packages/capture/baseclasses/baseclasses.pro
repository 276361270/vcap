TEMPLATE = lib

include(../../include/common.pri)

CONFIG += staticlib
CONFIG -= qt

# Input
HEADERS += 	\
            amextra.h       \
            amfilter.h      \
            cache.h         \
            checkbmi.h      \
            combase.h       \
            cprop.h         \
            ddmm.h          \
            dllsetup.h      \
            dxmperf.h       \
            fourcc.h        \
            measure.h       \
            msgthrd.h       \
            mtype.h         \
            outputq.h       \
            perflog.h       \
            perfstruct.h    \
            pstream.h       \
            pullpin.h       \
            refclock.h      \
            reftime.h       \
            renbase.h       \
            schedule.h      \
            seekpt.h        \
            source.h        \
            streams.h       \
            strmctrl.h      \
            sysclock.h      \
            transfrm.h      \
            transip.h       \
            videoctl.h      \
            vtrans.h        \
            winctrl.h       \
            winutil.h       \
            wxdebug.h       \
            wxlist.h        \
            wxutil.h
            

           
SOURCES += 	amextra.cpp     \
            amfilter.cpp    \
            amvideo.cpp     \
            arithutil.cpp   \
            combase.cpp     \
            cprop.cpp      \
            ctlutil.cpp     \
            ddmm.cpp        \
            dllentry.cpp    \
            dllsetup.cpp    \
            mtype.cpp       \
            outputq.cpp     \
            perflog.cpp     \
            pstream.cpp     \
            pullpin.cpp     \
            refclock.cpp    \
            renbase.cpp     \
            schedule.cpp    \
            seekpt.cpp      \
            source.cpp      \
            strmctl.cpp     \
            sysclock.cpp    \
            transfrm.cpp    \
            transip.cpp     \
            videoctl.cpp    \
            vtrans.cpp      \
            winctrl.cpp     \
            winutil.cpp     \
            wxdebug.cpp     \
            wxlist.cpp      \
            wxutil.cpp
            
            
