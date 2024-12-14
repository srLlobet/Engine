#pragma once

#include "Module.h"
#include "lib/MathGeoLib/Math/float4x4.h"
#include <vector>

using GLuint = unsigned int;

class Mesh;


class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();

	// Destructor
	virtual ~ModuleRenderExercise();

	bool Init();
	bool CleanUp();
	update_status Update(float deltaTime);

	void RenderVBO();
	unsigned CreateTriangleVBO();
	void DestroyVBO(unsigned vbo);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
	void RenderAllMeshes();
	void RenderMesh(const Mesh& mesh);
	void AddMesh(Mesh* mesh);
	void ClearMeshes();
	
private:


	unsigned program;

	std::vector<Mesh*> meshes;

	float4x4 model;
	float4x4 view;
	float4x4 projection;

	GLuint textureID;
	int modelLoc;
	int viewLoc;
	int projectionLoc;

};
