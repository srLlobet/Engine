#pragma once

#include "Module.h"

#include "Math/float4x4.h"


class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

public:

    ModuleDebugDraw();
    virtual ~ModuleDebugDraw();

	bool Init();
	update_status Update(float deltaTime);
	bool CleanUp();
    void Draw(const float4x4& view, const float4x4& proj, unsigned width, unsigned height);

private:

    static DDRenderInterfaceCoreGL* implementation;
};

