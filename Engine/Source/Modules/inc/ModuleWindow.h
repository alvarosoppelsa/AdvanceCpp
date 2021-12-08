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
	int GetScreenWidth() const { return ScreenSurface->w; };
	int GetScreenHeight() const { return ScreenSurface->h; };

	SDL_Window* window = NULL;

private:
	bool IsFullScreen = false;
	int RefreshRate;
	SDL_Surface* ScreenSurface = NULL;
};

#endif // __ModuleWindow_H__