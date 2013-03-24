#ifndef DSNCONFIG_H
#define DSNCONFIG_H

#ifndef DSNAPI
#define DSNAPI __declspec(dllexport)
#endif 

#include "streams.h"
#include "amfilter.h"
#include "renbase.h"
#include "transfrm.h"
#include <initguid.h>

#include "capture/ix264filter.h"

#include "inttypes.h"
#include "stdint.h"

extern "C" {
#include "x264/x264.h"
}

#endif