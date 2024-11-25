#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Globals.h"
#include <GL/glew.h> 
#include <GL/gl.h>

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
    program = ModuleProgram::CreateProgram("default_vertex.glsl", "default_fragment.glsl");
    if (program == 0) {
        LOG("Failed to create program");
        return false;
    }
    vbo = CreateTriangleVBO();
    if (vbo == 0) {
        LOG("Failed to create vbo");
        glDeleteProgram(program);
        return false;
    }

    frustum.type = FrustumType::PerspectiveFrustum;
    frustum.pos = float3::zero;         // Camera position
    //frustum.pos = float3(0.0f, 0.0f, 2.0f);
    frustum.front = -float3::unitZ;    // Looking towards -Z
    frustum.up = float3::unitY;        // Up direction
    frustum.nearPlaneDistance = 0.5f;
    frustum.farPlaneDistance = 100.0f;
    frustum.verticalFov = pi / 4.0f; // 45 degrees
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * SCREEN_WIDTH/SCREEN_HEIGHT); 
 

    //model = float4x4::identity; // No transformation
    view = frustum.ViewMatrix(); // Use frustum view matrix
    //view = float4x4::identity;
    projection = frustum.ProjectionMatrix();
    //projection = float4x4::identity;


	return true;
}

bool ModuleRenderExercise::CleanUp()
{
    glDeleteProgram(program);
    DestroyVBO(vbo);
	return false;
}

update_status ModuleRenderExercise::Update()
{
    RenderVBO();
    return UPDATE_CONTINUE;
}

void ModuleRenderExercise::RenderVBO()
{

    glUseProgram(program);

    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_TRUE, &projection[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // 1 triangle to draw = 3 vertices 
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
}

unsigned ModuleRenderExercise::CreateTriangleVBO()
{
    {
        float vtx_data[] = { -1.0f, -1.0f, -2.0f, 1.0f, -1.0f, -2.0f, 0.0f, 1.0f, -2.0f };
        unsigned vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);  // set vbo active 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

        return vbo;
    }
    // This function must be called one time at destruction of vertex buffer
    return 0;   
}

void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
    glDeleteBuffers(1, &vbo);
}
void ModuleRenderExercise::UpdateProjectionMatrix(float aspectRatio)
{
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
    projection = frustum.ProjectionMatrix();
}