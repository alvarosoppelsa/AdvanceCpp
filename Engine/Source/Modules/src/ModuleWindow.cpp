#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

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
	ENGINE_LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ENGINE_LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			ENGINE_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			ScreenSurface = SDL_GetWindowSurface(window);
		}

		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, 0, &mode);
		RefreshRate = mode.refresh_rate;
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	ENGINE_LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::WindowsSizeChanged()
{
	// Update window surface so it is correct
	SDL_UpdateWindowSurface(window);
	ScreenSurface = SDL_GetWindowSurface(window);
	App->renderer->WindowResized(ScreenSurface->w, ScreenSurface->h);
	//App->camera->WindowResized(screen_surface->w, screen_surface->h);
}
