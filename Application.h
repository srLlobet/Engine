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
class ModuleTexture;
class ModuleModel;
class Time;

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
    ModuleTexture* GetTexture() { return texture; }
    ModuleModel* GetModel() { return model; }
    ModuleEditor* GetEditor() { return editor; }



private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleRenderExercise* program = nullptr;
    ModuleDebugDraw* debug = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleTexture* texture = nullptr;
    ModuleModel* model = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
