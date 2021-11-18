#pragma once

#include "Module.h"
#include "ImGui/imgui_impl_opengl3_loader.h"
#include <IL/il.h>

class ModuleTexture : public Module
{
public:
	// TODO: we need to add texture path as a parameter to the constructor
	ModuleTexture();
	~ModuleTexture() = default;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	// from DevIL
	ILuint texid;
	ILboolean success;
	GLuint image;
	int finished;
};

