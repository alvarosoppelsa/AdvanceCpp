#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Model;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();


	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void UpdateWindowSize();
	bool LoadModule(const char* filePath);
	const Model* GetCurrentModel() const { return RenderModel; }
	void* GetContext() const
	{
		assert(Context != nullptr);
		return Context;
	}

private:
	int Width = 0;
	int Height = 0;
	Model* RenderModel;
	void* Context;
};
