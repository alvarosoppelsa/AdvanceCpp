#pragma once

#include "SDL.h"

// This class contains two independent
// timers of different pressition
class Timer
{
public:
	Timer() : Running(false)
	{
		CountToSeconds = 1 / SDL_GetPerformanceFrequency();
	}

	void StartMs()
	{
		Ms = SDL_GetTicks();
		Running = true;
	}

	// Returns current millisecond count
	const Uint32 ReadMs()
	{
		Ms = SDL_GetTicks() - Ms;
		return Ms;
	}

	// Stops the counting and returns count in milliseconds
	// Subsecuent calls will have the same effect as ReadMs
	const Uint32 StopMs()
	{
		if (Running)
		{
			Ms = SDL_GetTicks() - Ms;
			Running = false;
		}
		return Ms;
	}

	// Set time in ms to 0, don't stop if running
	void ResetMs()
	{
		Ms = 0;
	}

	void StartUs()
	{
		Us = SDL_GetPerformanceCounter();
		Running = true;
	}

	const Uint64 ReadUs()
	{
		return (SDL_GetPerformanceCounter() - Us) * CountToSeconds;
	}

	const Uint64 StopUs()
	{
		if (Running)
		{
			Us = (SDL_GetPerformanceCounter() - Us);
			Running = false;
		}
		return Us * CountToSeconds;
	}

	// Set time in us to 0, don't stop if running
	void ResetUs()
	{
		Us = 0;
	}

	const float ReadFps() const
	{
		return Fps;
	}

private:
	Uint32 Ms = 0;
	Uint64 Us = 0;
	float Fps = 0.0f;
	bool Running = false;
	Uint64 CountToSeconds;
};
