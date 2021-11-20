#pragma once

#define NOMINMAX

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleDebugDraw;
class ModuleTexture;
class ModuleRenderExercise;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer			= nullptr;
	ModuleWindow* window			= nullptr;
	ModuleInput* input				= nullptr;
	ModuleProgram* program			= nullptr;
	ModuleDebugDraw* draw			= nullptr;
	ModuleTexture* texture			= nullptr;
	ModuleRenderExercise* exercise  = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
