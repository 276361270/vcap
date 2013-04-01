#ifndef _CAMERAFACTORY_H
#define _CAMERAFACTORY_H

#include "vcapconfig.h"

class Camera;
class CameraFactory
{
public:
	static std::vector<Camera*>		enumCameras();

};

#endif