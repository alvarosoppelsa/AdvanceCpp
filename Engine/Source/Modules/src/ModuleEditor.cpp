#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "Model.h"
#include "Performance.h"
#include "Timer.h"

#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <SDL.h>

#define MAX_CONSOLE_OUTPUT 100
#define MAX_PERFORMANCE_LOG 60

using namespace ImGui;

ModuleEditor::ModuleEditor()
	: FixedFps(0)
	, FixFps(false)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    initialized = true;
    CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->GetContext());
    ImGui_ImplOpenGL3_Init("#version 330");
    ShowConsole = false;
    ShowAboutWindow = false;

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    update_status retVal = UPDATE_CONTINUE;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    NewFrame();

    if(!MainMenu())
    {
        retVal = UPDATE_STOP;
    }
    GeneralSettings();
    About();
    Console();
    FrameRate();

    return retVal;
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
    ConsoleOutputs.push_back(line);
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

inline void ModuleEditor::ModelSettings()
{
    const Model* model = App->renderer->GetCurrentModel();
    const std::vector<Mesh> meshes = model->GetMeshes();

	Separator();
	Text("Model");
	Text(model->GetDirectory().c_str());
    for (int i = 0; i < meshes.size(); ++i)
    {
        Separator();
    	Text("Mesh #%d", i);
        Text("Vertices: %d", meshes[i].GetNumVertices());
        Text("Indices: %d", meshes[i].GetNumIndices());
        Text("Textures: %d", meshes[i].GetNumTextures());
       
    }
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
    for (auto it = ConsoleOutputs.size() > MAX_CONSOLE_OUTPUT ? ConsoleOutputs.size() - MAX_CONSOLE_OUTPUT : 0;
        it < ConsoleOutputs.size(); ++it)
    {
        Text(ConsoleOutputs[it]);
    }
    if (ConsoleOutputs.size() == MAX_CONSOLE_OUTPUT * 10)
    {
        ConsoleOutputs.clear();
    }
    End();
}

inline void ModuleEditor::CameraSettings()
{
    Separator();
    Text("Translation");
    CameraPos = App->camera->GetPosition();
    if (SliderFloat3("X, Y, Z", &CameraPos[0], -250.0f, 250.0f))
    {
        App->camera->SetPosition(CameraPos);
    }

    Separator();
    Text("Rotation");
	SliderFloat3("Roll, Pitch, Yaw", &CameraRotation[0], 0.5f, 10.0f);

    Separator();
    Text("Projection");
    CameraAspect = App->camera->GetAspectRatio();

    Separator();
	ImGui::InputScalar("Aspect Ratio", ImGuiDataType_Float, &CameraAspect);

    Separator();
    CameraFOV = App->camera->GetHorizontalFovDegrees();
    if (SliderFloat("Horizontal FOV", &CameraFOV, 0.1f, 120.0f))
    {
        App->camera->SetHorizontalFovInDegrees(CameraFOV);
    }

    Separator();
    if (Button("Default Values"))
    {
        App->camera->SetDefaultValues();
    }
}

inline void ModuleEditor::WindowSettings()
{
    if (Button("Fullscreen", ImVec2(100, 30)))
    {
	    App->window->ToggleFullScreen();
    }
    Separator();
    SwapInterval();
}

inline void ModuleEditor::SwapInterval() const
{
    int swapInterval = SDL_GL_GetSwapInterval();
    if (RadioButton("Immediate Update",     &swapInterval, 0) ||
		RadioButton("Syncronized Updates",  &swapInterval, 1) ||
        RadioButton("Adaptive Vsync",       &swapInterval,-1))
    {
        App->window->SetSwapInterval(swapInterval);
    }
}

inline void ModuleEditor::GeneralSettings()
{
    ImGuiWindowFlags wFlags = 0;
    wFlags |= ImGuiWindowFlags_MenuBar;

	// TODO: Look up for docking flags
    Begin("General Settings", NULL, wFlags);
    if (!BeginMenuBar())
    {
        return;
    }

    Separator();
    if (BeginMenu("Editor Configuration"))
    {
        MenuItem("Console", NULL, &ShowConsole);
        Separator();
        MenuItem("Frame Rate", NULL, &ShowPerformanceWindow);
        ImGui::EndMenu();
    }

    EndMenuBar();
    Separator();
    if (CollapsingHeader("Window Settings"))
    {
        WindowSettings();
    }

    Separator();
    if (CollapsingHeader("Camera Settings"))
    {
        CameraSettings();
    }

    Separator();
    if (CollapsingHeader("Module Info"))
    {
        ModelSettings();
    }
    End();
}

inline bool ModuleEditor::MainMenu()
{
    if (!BeginMainMenuBar())
    {
        return false;
    }

    if (BeginMenu("File"))
	{
        MenuItem("New");
        MenuItem("Save");
        MenuItem("Load");
        if (MenuItem("Close"))
        {
            return false;
        }
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
    return true;
}

inline void ModuleEditor::FrameRate()
{
    if (!ShowPerformanceWindow)
    {
        FpsOutputs.clear();
        TimeMsOutputs.clear();
        return;
    }

    if (FpsOutputs.size() >= MAX_PERFORMANCE_LOG)
    {
        FpsOutputs.erase(FpsOutputs.begin());
    }

    FpsOutputs.push_back(App->performance->GetFps());
    if (TimeMsOutputs.size() >= MAX_PERFORMANCE_LOG)
    {
        TimeMsOutputs.erase(TimeMsOutputs.begin());
    }

    TimeMsOutputs.push_back(App->performance->GetDeltaTime());

    Begin("Performance Plots", &ShowPerformanceWindow);
    char title[25];
    float lastFps = FpsOutputs.back();
    sprintf_s(title, 25, "Framerate %.1f", lastFps);
    PlotHistogram("##Framerate", &FpsOutputs[0], FpsOutputs.size(), 0, title, 0.0f, lastFps + 50.0f, ImVec2(310, 100));

    float lastTimeMs = TimeMsOutputs.back();
    sprintf_s(title, 25, "Milliseconds %.1f", lastTimeMs);
    PlotHistogram("##milliseconds", &TimeMsOutputs[0], TimeMsOutputs.size(), 0, title, 0.0f, lastTimeMs + 10.0f, ImVec2(310, 100));

    End();
}
