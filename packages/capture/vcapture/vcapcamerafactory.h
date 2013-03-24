#ifndef VCAPCAMERAFACTORY_H
#define VCAPCAMERAFACTORY_H

#include "vcapconfig.h"

class VCapCamera;
class VCapCameraFactory
{
public:
	static std::vector<VCapCamera*>		enumCameras();

};

#endif