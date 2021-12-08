#pragma once

#define NOMINMAX

#include<list>
#include "Globals.h"
#include "Module.h"
#include "ModuleEditor.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleCamera;
class ModuleDebugDraw;
class ModuleTexture;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleCamera;
class Performance;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool IsShutingDown() { return ShuttingDown; };

	ModuleRender* renderer			= nullptr;
	ModuleWindow* window			= nullptr;
	ModuleInput* input				= nullptr;
	ModuleProgram* program			= nullptr;
	ModuleDebugDraw* ddraw			= nullptr;
	ModuleCamera* camera			= nullptr;
	ModuleEditor* editor			= nullptr;
	Performance* performance		= nullptr;

private:
	std::list<Module*> modules;
	bool ShuttingDown;
};

extern Application* App;
