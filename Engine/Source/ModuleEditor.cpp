#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

bool ModuleEditor::Init()
{
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init();
    show_demo_window = true;
    show_console = true;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    return true;
}

update_status ModuleEditor::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&show_demo_window);
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Show Console", &show_console);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    if (ImGui::BeginMenu("Help"))
    {

        ImGui::EndMenu();
    }

    //// Console
    //if (show_console)
    //{
    //    ImGui::Begin("Console", &show_console);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    //    while (!App->console_output.empty())
    //    {
    //        ImGui::TextUnformatted(App->console_output.front());
    //        App->console_output.pop();
    //    }
    //    //if (ImGui::Button("Close Me"))
    //    //    show_another_window = false;
    //    ImGui::End();
    //}

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PreUpdate()
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
