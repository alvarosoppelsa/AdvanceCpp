#pragma once

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"

class ImVec4;

class ModuleEditor : public Module
{
public:
	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;
private:
	bool show_demo_window;
	bool show_console;
	ImVec4 clear_color;
};

