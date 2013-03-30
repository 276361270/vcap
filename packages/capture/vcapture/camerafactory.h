#ifndef _CAMERAFACTORY_H
#define _CAMERAFACTORY_H

#include "vcapconfig.h"

class VCapCamera;
class CameraFactory
{
public:
	static std::vector<VCapCamera*>		enumCameras();

};

#endif