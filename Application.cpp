#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "ModuleInput.h"
#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"
#include "Logger.h"
#include "Time.h"

using namespace std;

Application::Application()
{	
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(render = new ModuleOpenGL());
	modules.push_back(input = new ModuleInput());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(program = new ModuleRenderExercise());
	modules.push_back(debug = new ModuleDebugDraw());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(model = new ModuleModel());
	
}

static Timer frameTimer;

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}



update_status Application::Update()
{

	float deltaTime = frameTimer.GetDeltaTime();

	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate(deltaTime);

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update(deltaTime);

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate(deltaTime);

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
