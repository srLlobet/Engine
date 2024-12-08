#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "Logger.h"

ModuleWindow::ModuleWindow()
{

}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	Logger::Instance().LOGS("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//, SDL_GetError()
		Logger::Instance().LOGS("SDL_VIDEO could not initialize! SDL_Error: %s\n");//, SDL_GetError()
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			Logger::Instance().LOGS("Window could not be created! SDL_Error: %s\n"); //, SDL_GetError()
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

void ModuleWindow::HandleWindowEvent(SDL_Event& event)
{
	if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		App->GetOpenGL()->WindowResized(event.window.data1, event.window.data2);
	}
}
// Called before quitting
bool ModuleWindow::CleanUp()
{
	Logger::Instance().LOGS("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

