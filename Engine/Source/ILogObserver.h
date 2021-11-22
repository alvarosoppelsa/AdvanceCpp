#pragma once

class ILogObserver
{
public:
	virtual void SubscribeToLogger() = 0;
	virtual void UnsubscribeToLogger() = 0;
	virtual void Log(char*) = 0;
};