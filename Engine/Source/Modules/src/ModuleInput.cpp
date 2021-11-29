#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ImGui/imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
    ENGINE_LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
        ENGINE_LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
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
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
            {
                return UPDATE_STOP;
            }
            case SDL_WINDOWEVENT:
            {
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->UpdateWindowSize();
                break;
            }
            // Mouse
            case SDL_MOUSEMOTION:
            {
                Motion.X = sdlEvent.motion.xrel;
                Motion.Y = sdlEvent.motion.yrel;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                MouseButton = sdlEvent.button;
                Motion = 0;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                MouseButton = sdlEvent.button;
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                MouseWheel = sdlEvent.wheel;
                break;
            }
            case SDL_DROPFILE:
            {   
                DroppedFileDir = sdlEvent.drop.file;

                break;
            }
        }
    }
    Keyboard = SDL_GetKeyboardState(NULL);
    Mouse = SDL_GetMouseState(&MouseX, &MouseY);
    return UPDATE_CONTINUE;
}

update_status ModuleInput::PostUpdate()
{
    if (DroppedFileDir == nullptr)
    {
        return UPDATE_CONTINUE;
    }
    
    if (!App->renderer->LoadModule(DroppedFileDir))
    {
        // Shows directory of dropped file
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION,
            "File not supported",
            DroppedFileDir,
            App->window->window);
    }
    SDL_free(DroppedFileDir);
    DroppedFileDir = nullptr;
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    ENGINE_LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
