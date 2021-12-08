#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"

ModuleWindow::ModuleWindow()
	: RefreshRate(0)
{
}

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
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;

		SDL_DisplayMode DM;
		if (!SDL_GetCurrentDisplayMode(0, &DM))
		{
			width = DM.w * 0.95;
			height = DM.h * 0.95;
		}
		
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			ENGINE_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		//Get window surface & configure
		ScreenSurface = SDL_GetWindowSurface(window);
		SDL_SetWindowResizable(window, SDL_TRUE);
		SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, 0, &mode);
		SetSwapInterval(1); // Vsync active
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
	SDL_UpdateWindowSurface(window);
	ScreenSurface = SDL_GetWindowSurface(window);
	App->renderer->UpdateWindowSize(ScreenSurface->w, ScreenSurface->h);
	App->camera->SetAspectRatio(ScreenSurface->w, ScreenSurface->h);
}

void ModuleWindow::ToggleFullScreen()
{
	if (IsFullScreen)
	{
		SDL_SetWindowFullscreen(window, 0);
		IsFullScreen = false;
	}
	else
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		IsFullScreen = true;
	}
}

void ModuleWindow::SetSwapInterval(int swapInterval) const
{
	ENGINE_LOG("ModuleWindow - SetSwapInterval: %d", swapInterval);
	if (SDL_GL_SetSwapInterval(swapInterval) == -1)
	{
		SDL_GL_SetSwapInterval(1);
	}
}

