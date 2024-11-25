#ifndef __ModuleCamera_H__
#define __ModuleCamera_H__

#include "Module.h"
class ModuleCamera : public Module
{
	ModuleCamera();
	~ModuleCamera();
	
	bool Init();
	void SetFOV(); //… should set the horizontal FOV keeping the aspect ratio
	void SetAspectRatio(); //… should change the vertical FOV to meet the new aspect ratio.
	void SetPlaneDistances(); // Position() / Orientation() / LookAt(x, y, z)
	void GetProjectionMatrix(); //OpenGL matrix order is different from default MathGeoLib!Math info here
	void GetViewMatrix(); //… OpenGL matrix order is different from default MathGeoLib!Math info here
};

#endif // __ModuleCamera_H__