#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise; 
class ModuleDebugDraw;
class ModuleEditor;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    ModuleCamera* GetCamera() { return camera; }
    ModuleRenderExercise* GetRenderExercise() { return program;}

private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleRenderExercise* program = nullptr;
    ModuleDebugDraw* debug = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleCamera* camera = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
