#include "ModuleCamera.h"
#include "Globals.h"
#include "lib/MathGeoLib/Math/float3.h"
#include "lib/MathGeoLib/Math/MathConstants.h"

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

    frustum.pos = float3(0.0f, -2.0f, 0.5f);       // Camera position
    frustum.front = -float3::unitZ;

    //frustum.front = -float3::unitZ;    // Looking towards -Z
    //frustum.front = float3(0.0f, 0.0f, 1.0f);
        //- frustum.pos).Normalized();
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

void ModuleCamera::RefreshViewMatrix() {

    view = float4x4(frustum.ViewMatrix()).Transposed();

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

//zoom
void ModuleCamera::SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
{
    frustum.nearPlaneDistance = nearPlaneDistance;
    frustum.farPlaneDistance = farPlaneDistance;

    projection = frustum.ProjectionMatrix().Transposed();
    
}

/*const float4x4 ModuleCamera::LookAt(const float3& cameraPosition, const float3& cameraDirection, const float3& upVector) {
    float3 zaxis = (cameraPosition - cameraDirection).Normalized();  // Camera is looking towards the target
    float3 xaxis = upVector.Cross(zaxis).Normalized();     // Right vector
    float3 yaxis = zaxis.Cross(xaxis);               // Up vector

    // Build the view matrix
    float4x4 matrix = float4x4::identity;
    matrix[0] = float4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
    matrix[1] = float4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
    matrix[2] = float4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
    matrix[3] = float4(-xaxis.Dot(cameraPosition), -yaxis.Dot(cameraPosition), -zaxis.Dot(cameraPosition), 1.0f);

    return matrix;
}

const float4x4& ModuleCamera::GetViewMatrix() const {
    return LookAt(frustum.pos, frustum.pos + frustum.front, frustum.up);
}
*/