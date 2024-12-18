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
	bool CleanUp();
	void DrawFpsGraph(float deltaTime);
	void DrawConsole();
	void RenderUI(float deltaTime);
	void DrawMenuBar();
	void AboutWindow();
	void DrawHardware();
	void DrawWindowOptions();

private:
	std::vector<float> fps_log;
	std::vector<float> ms_log;

	const size_t maxFpsSamples = 100;

	bool showDemoWindow;
	bool showAboutWindow;
	bool showHardwareWindow;
	bool showWindowOptions;
};