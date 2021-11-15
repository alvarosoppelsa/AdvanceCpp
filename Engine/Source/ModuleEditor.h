#pragma once

#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"
#include <vector>

class ImVec4;

class ModuleEditor : public Module
{
public:
	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;
	void ConsoleLog(char* line);
private:
	bool show_demo_window;
	bool show_console;
	bool show_about_window;
	ImVec4 clear_color;
	std::vector<char*> console_outputs;
};

