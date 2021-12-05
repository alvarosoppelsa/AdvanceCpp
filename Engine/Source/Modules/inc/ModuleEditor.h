#pragma once

#include "Module.h"
#include "Globals.h"

#include "ImGui/imgui.h"
#include "Math/float3.h"
#include <vector>

class ImVec4;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void ConsoleLog(char* line);

private:
	// General
	void GeneralSettings();
	bool MainMenu();

	// Performance
	bool ShowPerformanceWindow;
	int FixedFps;
	bool FixFps;
	std::vector<float> FpsOutputs;
	std::vector<float> TimeMsOutputs;
	void FrameRate();

	// Console
	bool ShowConsole;
	std::vector<char*> ConsoleOutputs;
	void Console();

	// Window
	bool FullScreenWindow;
	void WindowSettings();
	void SwapInterval() const;

	// Camera
	float CameraAspect;
	float CameraFOV;
	float3 CameraPos;
	float3 CameraRotation;
	void CameraSettings();

	// About
	bool ShowAboutWindow;
	void About();

	// Model
	void ModelSettings();
};

