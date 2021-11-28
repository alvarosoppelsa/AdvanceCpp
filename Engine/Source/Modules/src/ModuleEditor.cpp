#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <GL/glew.h>

#include "ModuleCamera.h"

#define MAX_CONSOLE_OUTPUT 100

using namespace ImGui;

bool ModuleEditor::Init()
{
    initialized = true;
    CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init("#version 330");
    ShowConsole = false;
    ShowAboutWindow = false;

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    NewFrame();

    MainMenu();
    GeneralSettings();
    About();
    Console();

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    DestroyContext();

	return true;
}

void ModuleEditor::ConsoleLog(char* line)
{
    console_outputs.push_back(line);
}

inline void ModuleEditor::About()
{
    if (!ShowAboutWindow)
    {
        return;
    }
    ImGuiWindowFlags wFlags = ImGuiWindowFlags_NoDecoration;
    Begin("About", &ShowAboutWindow, wFlags);
    Text("Super Awesome Engine");
    Text("This is some description about the engine.");
    Text("Alvaro Soppelsa");
    Text("ImGui - SDL - glew - OpenGL");
    Text("GNU GPL");
    End();
}

inline void ModuleEditor::Console()
{
    if (!ShowConsole)
    {
        return;
    }

    Begin("Console", &ShowConsole);

    // If vector size is greater than the max console output show MAX_CONSOLE_OUTPUT,
	// otherwise show all content from 0 to size
    for (auto it = console_outputs.size() > MAX_CONSOLE_OUTPUT ? console_outputs.size() - MAX_CONSOLE_OUTPUT : 0;
        it < console_outputs.size(); ++it)
    {
        Text(console_outputs[it]);
    }
    End();
}

void ModuleEditor::CameraSettings()
{
    Text("Translation");
    CameraPos = App->camera->GetPosition();
    if (SliderFloat3("X, Y, Z", &CameraPos[0], -5.0f, 5.0f))
    {
        App->camera->SetPosition(CameraPos);
    }
    Text("Rotation");
	SliderFloat3("Roll, Pitch, Yaw", &CameraRotation[0], 0.5f, 10.0f);

    Text("Projection");
    CameraAspect = App->camera->GetAspectRatio();

	ImGui::InputScalar("Aspect Ratio", ImGuiDataType_Float, &CameraAspect);

    CameraFOV = App->camera->GetHorizontalFovDegrees();
    if (SliderFloat("Horizontal FOV", &CameraFOV, 0.1f, 120.0f))
    {
        App->camera->SetHorizontalFovInDegrees(CameraFOV);
    }

    if (Button("Default Values"))
    {
        App->camera->SetDefaultValues();
    }
}

void ModuleEditor::WindowSettings()
{
}

void ModuleEditor::GeneralSettings()
{
    ImGuiWindowFlags wFlags = 0;
    wFlags |= ImGuiWindowFlags_MenuBar;

	// TODO: Look up for docking flags
    Begin("General Settings", NULL, wFlags);
    if (!BeginMenuBar())
    {
        return;
    }

    if (BeginMenu("Editor Configuration"))
    {
        MenuItem("Console", NULL, &ShowConsole);
        ImGui::EndMenu();
    }

    EndMenuBar();
    if (CollapsingHeader("Window Settings"))
    {
        WindowSettings();
    }

    if (CollapsingHeader("Camera Settings"))
    {
        CameraSettings();
    }

    End();
}

void ModuleEditor::MainMenu()
{
    if (!BeginMainMenuBar())
    {
        return;
    }

    if (BeginMenu("File"))
	{
        MenuItem("New");
        MenuItem("Save");
        MenuItem("Load");
        ImGui::EndMenu();
    }

    if (BeginMenu("Edit"))
    {
        MenuItem("Undo");
        MenuItem("Redo");
        ImGui::EndMenu();
    }

    if (BeginMenu("About"))
    {
        ShowAboutWindow = true;
        if (MenuItem("Close"))
        {
            ShowAboutWindow = false;
        }
        ImGui::EndMenu();
    }

    EndMainMenuBar();
}
