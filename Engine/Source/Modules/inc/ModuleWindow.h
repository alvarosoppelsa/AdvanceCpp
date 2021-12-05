#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:
	ModuleWindow();
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

	void WindowsSizeChanged();
	void ToggleFullScreen();
	void SetSwapInterval(int swapInterval) const;

	SDL_Window* window = NULL;
	SDL_Surface* ScreenSurface = NULL;

private:
	bool IsFullScreen = false;
	int RefreshRate;
};

#endif // __ModuleWindow_H__