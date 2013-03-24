#ifndef VCAPCONFIG_H
#define VCAPCONFIG_H

#include <Windows.h>
#include <ObjBase.h>
#include <strmif.h>
#include <uuids.h>
#include <control.h>
#include <string>
#include <vector>
#include <dshow.h>
#include <initguid.h>
#include "capture/idsrfilter.h"
#include "capture/idsxfilter.h"

#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include <qedit.h>

#include "capture/ivcapengine.h"

#include "speex/speex.h"

#endif