#ifndef __ModuleRenderExercise_H__
#define __ModuleRenderExercise__

#include "Module.h"
#include "lib/MathGeoLib/Math/float4x4.h"
#include "lib/MathGeoLib/Geometry/Frustum.h"
#include "lib/MathGeoLib/Math/float3.h"
#include "lib/MathGeoLib/Math/MathConstants.h"

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();

	// Destructor
	virtual ~ModuleRenderExercise();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	update_status Update();

	void RenderVBO();

	unsigned CreateTriangleVBO();

	const float4x4& GetProjectionMatrix() const { return projection; }
	const float4x4& GetViewMatrix() const { return view; }

	void UpdateProjectionMatrix(float aspectRatio);

	void DestroyVBO(unsigned vbo);

private:
	unsigned vbo;
	unsigned program;
	Frustum frustum;
	float4x4 model, view, projection;
};

#endif // __ModuleRenderExercise__