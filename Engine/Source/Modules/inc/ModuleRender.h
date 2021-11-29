#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Model;

class ModuleRenderExercise;

class ModuleRender : public Module
{
	friend ModuleRenderExercise;

public:
	ModuleRender();
	~ModuleRender();

	void* context;

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void UpdateWindowSize();

private:
	int Width = 0;
	int Height = 0;
	Model* RenderModel;
};
