#pragma once

#include "Globals.h"

class Application;

class Module
{
public:

	Module()
	{
	}

	virtual bool Init() 
	{
		initialized = true;
		return true; 
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual bool IsInitialized() { return initialized; }

protected:
	bool initialized = false;
};
