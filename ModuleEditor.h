#pragma once
#include "Module.h"
#include <memory>

class Logger;


class ModuleEditor : public Module
{
public:

	std::unique_ptr<Logger> logger;

	ModuleEditor();

	// Destructor
	virtual ~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool cleanup();
	void DrawFpsGraph();
	void DrawConsole();

private:
	std::vector<float> fpsBuffer;
	const size_t maxFpsBufferSize = 100;
};