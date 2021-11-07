#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

	void RenderVBO(unsigned vbo);
	
private:
	void* context;
	unsigned int vbo;
	unsigned int vao;
	unsigned int vertex_id;
	unsigned int fragment_id;
	unsigned int program;
};
