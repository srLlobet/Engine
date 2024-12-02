#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercise.h"
#include "imgui_impl_sdl2.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;

            case SDL_WINDOWEVENT:

                App->GetWindow()->HandleWindowEvent(sdlEvent);

                break;

            case SDL_KEYDOWN:

                if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
                    App->GetCamera()->MoveForward(true);  //  forward
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
                    App->GetCamera()->MoveForward(false); // camera backward
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
                    App->GetCamera()->MoveRight(true); // camera left
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
                    App->GetCamera()->MoveRight(false); // camera right
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q)
                    App->GetCamera()->MoveUp(true); // camera up
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E)
                    App->GetCamera()->MoveUp(false); // camera down

                App->GetRenderExercise()->UpdateViewMatrix();

                break;
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }
    
    keyboard = SDL_GetKeyboardState(NULL);

    
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
