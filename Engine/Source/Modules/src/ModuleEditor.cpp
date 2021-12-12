#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "Model.h"
#include "Performance.h"
#include "Tools.h"

#include <Psapi.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <SDL.h>

#define MAX_CONSOLE_OUTPUT 100
#define MAX_PERFORMANCE_LOG 60
#define TO_KBYTES 1/1024
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
    if (ShowGeneralSettings)
    {
        GeneralSettings();
    }
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

	for (auto it : ConsoleOutputs)
    {
        delete it;
    }
    ConsoleOutputs.clear();

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
    Begin("About", &ShowAboutWindow);
    Text("Game Engine");
    Text("This Game Engine has been developed for the\n UPC Master degree: 'Advance Programming for AAA Video Games'");
    Separator();
	Text("by Alvaro Soppelsa");
    if (ImGui::Button("Github Repository", ImVec2(ImGui::GetContentRegionAvailWidth(), 0)))
    {
        // If Button is clicked, open the repository link in browser:
        Tools::OpenLink(MY_REPO);
    }
    Separator();
    Text("Libraries Used");
    TextWrapped(LIBRARIES_USED);
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

void ModuleEditor::Lighting()
{
    float3 lightPosition = App->renderer->GetLightPosition();
    float3 lightColor = App->renderer->GetLightColor();
    float diffuseIntensity = App->renderer->GetDiffuseLightIntensity();
    float ambientIntensity = App->renderer->GetAmbientLightIntensity();
    float specularIntensity = App->renderer->GetSpecularLightIntensity();

    if (SliderFloat("Diffuse Light Intensity", &diffuseIntensity, 0.0f, 10.0f))
    {
        App->renderer->SetDiffuseLightIntensity(diffuseIntensity);
    }

    if (SliderFloat("Specular Light Intensity", &specularIntensity, 0.0f, 10.0f))
    {
        App->renderer->SetSpecularLightIntensity(specularIntensity);
    }

    if (SliderFloat("Ambient Light Intensity", &ambientIntensity, 0.0f, 1.0f))
    {
        App->renderer->SetAmbientLightIntensity(ambientIntensity);
    }
    
    Separator();
    Text("Light Position");
    if (SliderFloat3("X, Y, Z", &lightPosition[0], -100.0f, 100.0f))
    {
        App->renderer->SetLightPosition(lightPosition);
    }
    
    Separator();
    Text("Light Color");
    if (ImGui::ColorPicker3("R, G, B", &lightColor[0]))
    {
        App->renderer->SetLightColor(lightColor);
    }

}

inline void ModuleEditor::Console()
{
    if (!ShowConsole)
    {
        return;
    }

    Begin("Console", &ShowConsole);

    HoveredViewport = !IsWindowHovered();
    
    // If vector size is greater than the max console output show MAX_CONSOLE_OUTPUT,
	// otherwise show all content from 0 to size
    for (auto it = ConsoleOutputs.size() > MAX_CONSOLE_OUTPUT ? ConsoleOutputs.size() - MAX_CONSOLE_OUTPUT : 0;
        it < ConsoleOutputs.size(); ++it)
    {
        Text(ConsoleOutputs[it]);
        Separator();
    }
    if (ConsoleOutputs.size() == MAX_CONSOLE_OUTPUT)
    {
        for(auto it : ConsoleOutputs)
        {
            delete it;
        }
        ConsoleOutputs.clear();
    }
    End();
}

inline void ModuleEditor::CameraSettings()
{
    Separator();
    Text("Translation");
    float3 cameraPos = App->camera->GetPosition();
    if (SliderFloat3("X, Y, Z", &cameraPos[0], -250.0f, 250.0f))
    {
        App->camera->SetPosition(cameraPos);
    }

 //   Separator();
 //   Text("Rotation");
	//SliderFloat3("Yaw, Pitch, Roll", &CameraRotation[0], 0.5f, 10.0f);

    Separator();
    Text("Camera Speed");
    Separator();
    float speed = App->camera->GetMoveSpeed();
    if( SliderFloat("Move Speed", &speed, 0.001f, 0.5f))
    {
        App->camera->SetMoveSpeed(speed);
    }
    Separator();
    speed = App->camera->GetRotationSpeed();
    if (SliderFloat("Rotation Speed", &speed, 0.0001f, 0.05f))
    {
        App->camera->SetRotationSpeed(speed);
    }
    Separator();
    speed = App->camera->GetZoomPosSpeed();
    if (SliderFloat("Zoom Speed", &speed, 0.01f, 1.0f))
    {
        App->camera->SetZoomPosSpeed(speed);
    }
    Separator();
    speed = App->camera->GetOrbitSpeed();
    if (SliderFloat("Orbit Speed", &speed, 0.001f, 0.05f))
    {
        App->camera->SetOrbitSpeed(speed);
    }

    Separator();
    Text("Projection");
    float cameraAspect = App->camera->GetAspectRatio();

    Separator();
	ImGui::InputScalar("Aspect Ratio", ImGuiDataType_Float, &cameraAspect);

    Separator();
    float cameraFOV = App->camera->GetHorizontalFovDegrees();
    if (SliderFloat("Horizontal FOV", &cameraFOV, 0.1f, 120.0f))
    {
        App->camera->SetHorizontalFovInDegrees(cameraFOV);
    }

    Separator();
    if (Button("Default Values"))
    {
        App->camera->SetDefaultValues();
    }
}

inline void ModuleEditor::WindowSettings() const
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
	wFlags |= ImGuiWindowFlags_NoCollapse;
	wFlags |= ImGuiWindowFlags_AlwaysAutoResize;

	// TODO: Look up for docking flags
    Begin("General Settings", NULL, wFlags);
    if (!BeginMenuBar())
    {
        return;
    }

    HoveredViewport = !IsWindowHovered();

    Separator();
    if (BeginMenu("Editor Tools"))
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

    Separator();
    if (CollapsingHeader("Lighting"))
    {
        Lighting();
    }

    Separator();
    if (CollapsingHeader("System"))
    {
        SystemInfo();
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

    if (BeginMenu("View"))
    {
        MenuItem("General Settings", NULL, &ShowGeneralSettings);
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

void ModuleEditor::SystemInfo()
{
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(),
        &memCounter,
        sizeof(memCounter));
    Separator();
    Text("GPU: %s", glGetString(GL_VENDOR));
    Text("Driver: %s", glGetString(GL_RENDERER));
    Text("Memory Consumption: %d Kb", memCounter.WorkingSetSize * TO_KBYTES);
    Separator();
    Text("OpenGL v%s", glGetString(GL_VERSION));
    Text("Glew v%s", glewGetString(GLEW_VERSION));
    Text("GLSL v%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

}
