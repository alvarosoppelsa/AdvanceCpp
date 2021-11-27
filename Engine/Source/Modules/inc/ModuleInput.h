#pragma once
#include "Module.h"
#include "Globals.h"

#include "SDL.h"

typedef unsigned __int8 Uint8;

struct MouseMotion
{
	int X;
	int Y;

	void operator=(int value)
	{
		X = value;
		Y = value;
	}
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	const unsigned GetKeyboard(SDL_Scancode key) const
	{
		return Keyboard[key];
	}

	const Uint32 GetMouseEvent()
	{
		return Mouse;
	}

	const MouseMotion& GetMouseMotion()
	{
		return Motion;
	}

	const SDL_MouseButtonEvent GetMouseButton()
	{
		return MouseButton;
	}

	const int GetMouseWheelDeltaY()
	{
		// TODO: This does not work
		WheelDeltaY = MouseWheel.y - WheelDeltaY;
		return WheelDeltaY;
	}

private:
	const Uint8* Keyboard = NULL;
	Uint32 Mouse;
	SDL_MouseButtonEvent MouseButton;
	SDL_MouseWheelEvent MouseWheel;
	MouseMotion Motion;
	int MouseX;
	int MouseY;
	int WheelDeltaY;
};