    #include "ModuleCamera.h"
    #include "Globals.h"
    #include "lib/MathGeoLib/Math/float3.h"
    #include "lib/MathGeoLib/Math/MathConstants.h"
    #include "lib/MathGeoLib/Math/Quat.h"

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


        frustum.pos = float3(0.0f, 2.0f, 10.0f);   // Camera position
        frustum.front = -float3::unitZ;
        frustum.up = float3::unitY;        // Up direction

    

        SetFOV(pi / 4.0f, SCREEN_WIDTH/ float(SCREEN_HEIGHT));
        //view = float4x4::identity;
        SetPlaneDistances(0.1f, 100.0f);

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
        projection = frustum.ProjectionMatrix();
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

    void ModuleCamera::RotatePitch(float angle)
    {
        Quat rotation = Quat::RotateAxisAngle(frustum.WorldRight(), angle);

        frustum.front = rotation.Transform(frustum.front).Normalized();
        frustum.up = rotation.Transform(frustum.up).Normalized();

        RefreshViewMatrix();
    }

    void ModuleCamera::RotateYaw(float  angle)
    {
        Quat rotation = Quat::RotateAxisAngle(float3::unitY, angle);

        frustum.front = rotation.Transform(frustum.front).Normalized();
        frustum.up = rotation.Transform(frustum.up).Normalized();

        RefreshViewMatrix();
    }


    //zoom
    void ModuleCamera::SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
    {
        frustum.nearPlaneDistance = nearPlaneDistance;
        frustum.farPlaneDistance = farPlaneDistance;

        projection = frustum.ProjectionMatrix();
    
    }

    void ModuleCamera::RefreshViewMatrix() {

       //LookAt(frustum.pos, frustum.front, frustum.up);
        view =  frustum.ViewMatrix();
    }

    //I tried
    void ModuleCamera::LookAt(const float3& cameraEye, const float3& cameraTarget, const float3& cameraUp) {

        float3 forward = (cameraTarget - cameraEye).Normalized();  // Camera is looking towards the target
        float3 right = Cross(forward,cameraUp).Normalized();     // Right vector
        float3 up = Cross(right,forward);               // Up vector
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

