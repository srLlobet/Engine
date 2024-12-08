#include "ModuleCamera.h"
#include "Globals.h"
#include "lib/MathGeoLib/Math/float3.h"
#include "lib/MathGeoLib/Math/MathConstants.h"
#include "Logger.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
 
    frustum.type = FrustumType::PerspectiveFrustum;
    //frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);

    frustum.pos = float3::zero;   // Camera position
    frustum.front = -float3::unitZ;
    frustum.up = float3::unitY;        // Up direction

    

    SetFOV(pi / 4.0f, SCREEN_WIDTH/ float(SCREEN_HEIGHT));
    //view = float4x4::identity;
    SetPlaneDistances(0.2f, 100.0f);

    RefreshViewMatrix();

	return true;
}

void ModuleCamera::SetFOV(float verticalFov, float aspectRatio)
{
    frustum.verticalFov = verticalFov; // Set vertical FOV
    RecalculateHorizontalFov(aspectRatio); // Recalculate the horizontal FOV based on the vertical FOV and aspect ratio

}

void ModuleCamera::RecalculateHorizontalFov(float aspectRatio)
{
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
    projection = frustum.ProjectionMatrix().Transposed();
}



void ModuleCamera::MoveForward(bool moveForward)
{
    if (moveForward)
        frustum.pos += frustum.front * MOVESPEED; // Move forward
    else
        frustum.pos -= frustum.front * MOVESPEED;

    RefreshViewMatrix();
}

void ModuleCamera::MoveRight(bool moveRight)
{
    if (moveRight)
        frustum.pos += frustum.WorldRight() * MOVESPEED; // Move right
    else
        frustum.pos -= frustum.WorldRight() * MOVESPEED; // Move left
    RefreshViewMatrix();
}

void ModuleCamera::MoveUp(bool moveUp)
{
    if (moveUp)
        frustum.pos += frustum.up * MOVESPEED; // Move up
    else
        frustum.pos -= frustum.up * MOVESPEED; // Move down

    RefreshViewMatrix();
}

void ModuleCamera::RotatePitch(bool rotateUp)
{

}

void ModuleCamera::RotateYaw(bool rotateRight)
{
}


//zoom
void ModuleCamera::SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
{
    frustum.nearPlaneDistance = nearPlaneDistance;
    frustum.farPlaneDistance = farPlaneDistance;

    projection = frustum.ProjectionMatrix().Transposed();
    
}

void ModuleCamera::RefreshViewMatrix() {

    LookAt(frustum.pos, frustum.front, frustum.up);
}

void ModuleCamera::LookAt(const float3& cameraEye, const float3& cameraTarget, const float3& cameraUp) {

    float3 forward = (cameraTarget - cameraEye).Normalized();  // Camera is looking towards the target
    float3 right = Cross(forward,cameraUp).Normalized();     // Right vector
    float3 up = Cross(right,forward).Normalized();               // Up vector
    float3 position = cameraEye;

    // Build the view matrix
    float4x4 camera = float4x4::identity;
    camera.SetCol3(0, right);  // X-axis
    camera.SetCol3(1, up);  // Y-axis
    camera.SetCol3(2, -forward);  // Z-axis
    camera.SetCol3(3, position);

    float4x4 translation = float4x4::identity;
    translation.SetTranslatePart(-cameraEye);

    float4x4 viewMatrix = camera * translation; //view matrix

    view = viewMatrix.Transposed();
}

