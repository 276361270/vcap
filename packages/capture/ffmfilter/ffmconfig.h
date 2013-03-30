#ifndef FFMCONFIG_H
#define FFMCONFIG_H

#ifndef FFMNAPI
#define FFMNAPI __declspec(dllexport)
#endif 

extern "C"{
#ifdef __cplusplus
 #define __STDC_CONSTANT_MACROS
 #ifdef _STDINT_H
  #undef _STDINT_H
 #endif
 # include <stdint.h>
#endif
}

#include "streams.h"
#include "amfilter.h"
#include "renbase.h"
#include "transfrm.h"
#include <initguid.h>

#include "inttypes.h"
#include "stdint.h"

extern "C" {
#include "stdint.h"
#include "inttypes.h"
#include "libavutil/avutil.h"
#include "libavutil/dict.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
}

#include "capture/iffmfilter.h"

#endif