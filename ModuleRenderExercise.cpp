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

    //cache
    modelLoc = glGetUniformLocation(program, "model");
    viewLoc = glGetUniformLocation(program, "view");
    projectionLoc = glGetUniformLocation(program, "projection");


    model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
        float4x4::identity,
        float3(100.0f, 100.0f, 100.0f)); // No transformation
        

	return true;
}

bool ModuleRenderExercise::CleanUp()
{
    glDeleteProgram(program);
    ClearMeshes();
	return false;
}

update_status ModuleRenderExercise::Update(float deltaTime)
{
    RenderAllMeshes();
    return UPDATE_CONTINUE;
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




//rendering gltf mesh
void ModuleRenderExercise::RenderMesh(const Mesh& mesh) {
    glUseProgram(program);

    glActiveTexture(GL_TEXTURE0);

    UpdateViewMatrix();

    glBindTexture(GL_TEXTURE_2D, mesh.GetMaterial().baseColorTextureID);
    glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

    glUniform4fv(glGetUniformLocation(program, "baseColorFactor"), 1, mesh.GetMaterial().baseColorFactor);
    glUniform1f(glGetUniformLocation(program, "metallicFactor"), mesh.GetMaterial().metallicFactor);

    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection[0][0]);

    glBindVertexArray(mesh.GetVAO());
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

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

