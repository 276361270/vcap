#ifndef SPXCONFIG_H
#define SPXCONFIG_H

#ifndef SPXNAPI
#define SPXNAPI __declspec(dllexport)
#endif 

#include "streams.h"
#include "amfilter.h"
#include "renbase.h"
#include "transfrm.h"
#include <initguid.h>

#include "capture/ispxfilter.h"

#include "inttypes.h"
#include "stdint.h"

extern "C" {
#include "speex/speex.h"
}

#endif