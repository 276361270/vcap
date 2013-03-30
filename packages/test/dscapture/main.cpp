#include "stdafx.h"
#include "dscapture.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DSCapture* capture = new DSCapture();
	capture->start();
	return 0;
}
