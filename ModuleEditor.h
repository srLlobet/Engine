#pragma once
#include "Module.h"
#include <memory>
#include <vector>

class Logger;


class ModuleEditor : public Module
{
public:

	std::unique_ptr<Logger> logger;

	ModuleEditor();

	// Destructor
	virtual ~ModuleEditor();

	bool Init();
	update_status PreUpdate(float deltaTime);
	update_status Update(float deltaTime);
	update_status PostUpdate(float deltaTime);
	bool cleanup();
	void DrawFpsGraph();
	void DrawConsole();

private:
	//std::vector<float> fpsBuffer;
	//const size_t maxFpsBufferSize = 100;
};