#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleOpenGL.h"
#include "lib/MathGeoLib/Math/MathConstants.h"
#include "Mesh.h"


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

    textureID = App->GetOpenGL()->LoadTextureToGPU(L"Test-image-Baboon.png");

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


    model = float4x4::FromTRS(float3(0.0f, 0.0f, -2.0f),
        float4x4::identity,
        float3(1.0f, 1.0f, 1.0f)); // No transformation
        


	return true;
}

bool ModuleRenderExercise::CleanUp()
{
    glDeleteProgram(program);
    DestroyVBO(vbo);
    ClearMeshes();
	return false;
}

update_status ModuleRenderExercise::Update(float deltaTime)
{
    //RenderVBO();
    RenderAllMeshes();
    return UPDATE_CONTINUE;
}

void ModuleRenderExercise::RenderVBO()
{

    glUseProgram(program);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, textureID);

    UpdateViewMatrix();

    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection[0][0]);



    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 3)); // buffer offset
    

    // 1 triangle to draw = 3 vertices 
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned ModuleRenderExercise::CreateTriangleVBO()
{
    { //{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
       // float vtx_data[] = { -1.0f, -1.0f, -2.0f, 1.0f, -1.0f, -2.0f, 0.0f, 1.0f, -2.0f };

        float vtx_data[] = {
            // Positions       // UVs
            -1.0f, -1.0f, -2.0f, 0.0f, 1.0f, // Bottom-left
             1.0f, -1.0f, -2.0f, 1.0f, 1.0f, // Bottom-right
             1.0f,  1.0f, -2.0f, 1.0f, 0.0f, // Top-right

            -1.0f, -1.0f, -2.0f, 0.0f, 1.0f, // Bottom-left
             1.0f,  1.0f, -2.0f, 1.0f, 0.0f, // Top-right
            -1.0f,  1.0f, -2.0f, 0.0f, 0.0f  // Top-left
        };
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

void ModuleRenderExercise::RenderAllMeshes()
{
    for (Mesh* mesh : meshes) {
        RenderMesh(*mesh);
    }
}


void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
    glDeleteBuffers(1, &vbo);
}

//rendering gltf mesh
void ModuleRenderExercise::RenderMesh(const Mesh& mesh) {
    glUseProgram(program);

    glActiveTexture(GL_TEXTURE5);

    UpdateViewMatrix();

    glBindTexture(GL_TEXTURE_2D, mesh.GetMaterial().baseColorTextureID);
    glUniform1i(glGetUniformLocation(program, "diffuse"), 5);

    glUniform4fv(glGetUniformLocation(program, "baseColorFactor"), 1, mesh.GetMaterial().baseColorFactor);
    glUniform1f(glGetUniformLocation(program, "metallicFactor"), mesh.GetMaterial().metallicFactor);

    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection[0][0]);

    glBindVertexArray(mesh.GetVAO());
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    /*
    glBindBuffe r(GL_ARRAY_BUFFER, mesh.GetVBO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetEBO());

    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // 3 floats per vertex (position)
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * mesh.GetVertexCount()));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Offset to UVs

    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    */
}

void ModuleRenderExercise::AddMesh(Mesh* mesh)
{
    
    meshes.push_back(mesh);
}

void ModuleRenderExercise::ClearMeshes()
{
    for (Mesh* mesh : meshes) {
       delete mesh;
       meshes.clear();
    }
}

