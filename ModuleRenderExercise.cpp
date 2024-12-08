#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "lib/MathGeoLib/Math/MathConstants.h"


ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
    program = ModuleProgram::CreateProgram("default_vertex.glsl", "default_fragment.glsl");
    
    //locations cache
    modelLoc = glGetUniformLocation(program, "model");
    viewLoc = glGetUniformLocation(program, "view");
    projectionLoc = glGetUniformLocation(program, "projection");


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

    model = float4x4::identity;
        /*float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
        float4x4::RotateZ(pi / 4.0f),
        float3(2.0f, 1.0f, 1.0f)); // No transformation
        */


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



    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection[0][0]);



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
    { //{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
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

void ModuleRenderExercise::UpdateViewMatrix() {

    view = App->GetCamera()->GetViewMatrix();

}
void ModuleRenderExercise::UpdateProjectionMatrix() {


    projection = App->GetCamera()->GetProjectionMatrix();

}

void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
    glDeleteBuffers(1, &vbo);
}
