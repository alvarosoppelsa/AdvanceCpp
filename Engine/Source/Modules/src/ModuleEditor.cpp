#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <GL/glew.h>

#define MAX_CONSOLE_OUTPUT 10000

bool ModuleEditor::Init()
{
    this->initialized = true;
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init("#version 330");
    show_demo_window = false;
    ShowConsole = false;
    ShowAboutWindow = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    return true;
}



update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Engine Configuration");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Checkbox("Show Console", &ShowConsole);
        ImGui::Checkbox("About", &ShowAboutWindow);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //Camera
        {
            ImGui::BeginChild("Camera Options",ImVec2(250.0, 100.0), true);
            {
                ImGui::Text("Application average");
                ImGui::SliderFloat("X Position", &f, 0.0f, 10.0f);
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }

    // About
    if (ShowAboutWindow)
    {
        ImGui::Begin("About", &ShowAboutWindow);
        ImGui::Text("Super Awesome Engine");
        ImGui::Text("This is some description about the engine.");
        ImGui::Text("Alvaro Soppelsa");
        ImGui::Text("ImGui - SDL - glew - OpenGL");
        ImGui::Text("GNU GPL");
        ImGui::End();
    }

    // Console
    if (ShowConsole)
    {
        ImGui::Begin("Console", &ShowConsole);
        // If vector size is greater than the max console output show MAX_CONSOLE_OUTPUT, otherwise show all content from 0 to size
        for (auto it = console_outputs.size() > MAX_CONSOLE_OUTPUT ? console_outputs.size() - MAX_CONSOLE_OUTPUT : 0;
            it < console_outputs.size(); ++it)
        {
            ImGui::Text(console_outputs[it]);
        }
        ImGui::End();
    }

    return UPDATE_CONTINUE;
}


update_status ModuleEditor::Update()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    ImGui::DestroyContext();
	return true;
}

void ModuleEditor::ConsoleLog(char* line)
{
    console_outputs.push_back(line);
}
