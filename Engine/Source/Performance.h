#pragma once
#include "Timer.h"

#define FRAME_BUFFER_SIZE 60
#define MS_TO_SECONDS 1e-3

class Performance
{
public:
	Performance() = default;
	~Performance() = default;

	void Start()
	{
		TimeCounter.StartMs();
	}

	void Stop()
	{
		TimeCounter.StopMs();
	}

	void Snapshot()
	{
		DeltaTime = TimeCounter.ReadMs();
		AccumulatedTime += DeltaTime;

		Index = (Index + 1) % FRAME_BUFFER_SIZE;
		if (!Index)
		{
			AccumulatedTime = DeltaTime;
			CurrentFrame = 0;
		}
		FrameHistory[Index] = DeltaTime;
		++CurrentFrame;
		Fps = CalculateFps();
	}

	float GetFps() const
	{
		return Fps;
	}

	float GetDeltaTime() const
	{
		return DeltaTime;
	}

	float CalculateFps()
	{
		if (CurrentFrame < FRAME_BUFFER_SIZE)
		{
			return (float)CurrentFrame / (AccumulatedTime * MS_TO_SECONDS);
		}

		return FRAME_BUFFER_SIZE / (AccumulatedTime * MS_TO_SECONDS);
	}
	
private:
	Timer TimeCounter;
	size_t Index = 0;
	unsigned int CurrentFrame = 0;
	float Fps = 0.0f;
	float FrameHistory[FRAME_BUFFER_SIZE] = {0.0f};
	float DeltaTime = 0.0f;
	float AccumulatedTime = 0.0f;
};