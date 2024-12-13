#pragma once

#include "Module.h"
#include "lib/MathGeoLib/Math/float4x4.h"

<<<<<<< HEAD
using GLuint = unsigned int;
=======
class Mesh;
>>>>>>> test

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
	void RenderMesh(Mesh mesh);

private:
	unsigned vbo;
	unsigned program;

	float4x4 model;
	float4x4 view;
	float4x4 projection;

	GLuint textureID;
	int modelLoc;
	int viewLoc;
	int projectionLoc;

};
