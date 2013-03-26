#ifndef PROTOCONFIG_H
#define PROTOCONFIG_H

#define    WIN32_LEAN_AND_MEAN
#include <string>
#include "core/int_types.h"
#include "core/packet.h"
#include "core/iproxy.h"
#include "core/const.h"

#ifdef _WIN32
#pragma warning(disable:4251)
#define SESSCOMM_API	__declspec( dllexport ) 

#else
#include <iconv.h>

#define SESSCOMM_API

#endif

#endif
