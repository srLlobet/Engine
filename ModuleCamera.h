#pragma once

#include "Module.h"
#include "lib/MathGeoLib/Math/float4x4.h"
#include "lib/MathGeoLib/Geometry/Frustum.h"


class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();
	
	bool Init();
	void SetFOV(float verticalFov, float aspectRatio); //� should set the horizontal FOV keeping the aspect ratio
	void SetPlaneDistances(float nearPlane, float farPlane);  // Position() / Orientation() / LookAt(x, y, z)
	void RecalculateHorizontalFov(float aspectRatio); //� should change the vertical FOV to meet the new aspect ratio
	void MoveForward(bool moveForward);
	void MoveRight(bool moveRight);
	void MoveUp(bool moveUp);
	void RotatePitch(float angle );
	void RotateYaw(float angle);



	void RefreshViewMatrix();


	const float4x4& GetProjectionMatrix() const { return projection; }
	const float4x4& GetViewMatrix() const { return view; };

	void LookAt(const float3& cameraPosition, const float3& cameraDirection, const float3& upVector);

private:
	Frustum frustum;
	float4x4 projection; // Projection matrix
	float4x4 view;       // View matrix
};
