#pragma once

#include "SDL.h"

class Timer
{
public:
	Timer()
	{
		countToSeconds = 1 / SDL_GetPerformanceFrequency();
	}

	void StartMS()
	{
		ms = SDL_GetTicks();
		running = true;
	}

	Uint32 ReadMS()
	{
		return SDL_GetTicks() - ms;
	}

	Uint32 StopMS()
	{ 
		if (running)
		{
			ms = SDL_GetTicks() - ms;
			running = false;
		}
		return ms;
	}

	void ResetMS()
	{ 
		ms = 0;
		running = false;
	}

	void StartUS()
	{
		us = SDL_GetPerformanceCounter();
		running = true;
	}

	Uint64 ReadUS()
	{
		return (SDL_GetPerformanceCounter() - us) * countToSeconds;
	}

	Uint64 StopUS()
	{
		if (running)
		{
			us = (SDL_GetPerformanceCounter() - us);
			running = false;
		}
		return us * countToSeconds;
	}

	void ResetMS()
	{
		ms = 0;
		running = false;
	}
private:
	Uint32 ms = 0;
	Uint64 us = 0;
	bool running = false;
	static Uint64 countToSeconds;
};

