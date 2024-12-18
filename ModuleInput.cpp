#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleModel.h"
#include "ModuleRenderExercise.h"
#include "imgui_impl_sdl2.h"
#include "Logger.h"
#include "Globals.h"

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
update_status ModuleInput::Update(float deltaTime)
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
                    App->GetCamera()->MoveForward(true, deltaTime);  //  forward
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
                    App->GetCamera()->MoveForward(false, deltaTime); // camera backward
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
                    App->GetCamera()->MoveRight(true, deltaTime); // camera left
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
                    App->GetCamera()->MoveRight(false, deltaTime); // camera right
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q)
                    App->GetCamera()->MoveUp(true, deltaTime); // camera up
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E)
                    App->GetCamera()->MoveUp(false, deltaTime); // camera down


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

                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {

                    const float mouseSensitivity = 0.001f; 
                    float deltaX = sdlEvent.motion.xrel; 
                    float deltaY = sdlEvent.motion.yrel; 

                    App->GetCamera()->RotateYaw(-deltaX * mouseSensitivity); // Inverted for right-to-left movement
                    App->GetCamera()->RotatePitch(-deltaY * mouseSensitivity); // Inverted for upward movement
                 }
                
                break;
            }

            case SDL_MOUSEWHEEL: {
                int y = sdlEvent.wheel.y;

                if (y > 0) {
                    // Zoom In
                    App->GetCamera()->ZoomIn();
                }
                else if (y < 0) {
                    // Zoom Out
                    App->GetCamera()->ZoomOut();
                }
                break;
            }


            case SDL_DROPFILE: {
                    const char* filePath = sdlEvent.drop.file;
                    App->GetModel()->LoadFromDragAndDrop(filePath);
                    SDL_free(sdlEvent.drop.file);
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
