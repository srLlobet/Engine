#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercise.h"
#include "imgui_impl_sdl2.h"
#include "Logger.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
    Logger::Instance().LOGS("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
        Logger::Instance().LOGS("SDL_EVENTS could not initialize! SDL_Error: %s\n"); //, SDL_GetError()
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


                if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
                    App->GetCamera()->RotatePitch(true);
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
                    App->GetCamera()->RotatePitch(false);
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    App->GetCamera()->RotateYaw(true);
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    App->GetCamera()->RotateYaw(false);

                App->GetRenderExercise()->UpdateViewMatrix();

                break;

            case SDL_MOUSEMOTION: {

                const float mouseSensitivity = 0.001f; // Adjust as needed
                float deltaX = sdlEvent.motion.xrel; // Horizontal motion
                float deltaY = sdlEvent.motion.yrel; // Vertical motion

                App->GetCamera()->RotateYaw(-deltaX * mouseSensitivity); // Inverted for right-to-left movement
                App->GetCamera()->RotatePitch(-deltaY * mouseSensitivity); // Inverted for upward movement
                break;
            }
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }
    
    keyboard = SDL_GetKeyboardState(NULL);

    
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    Logger::Instance().LOGS("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
