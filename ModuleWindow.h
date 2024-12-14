#pragma once

#include "Module.h"
#include <SDL.h>

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	void HandleWindowEvent(SDL_Event& event);


	virtual ~ModuleWindow();


	bool Init();


	bool CleanUp();
	
public:

	SDL_Window* window = NULL;


	SDL_Surface* screen_surface = NULL;
};
