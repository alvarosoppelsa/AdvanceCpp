#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "Model.h"

#include <cassert>

#include "SDL.h"
#include "GL/glew.h"

#include "Math/float4x4.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"

static const char* bakerHouseModel = ".\\Resources\\Models\\BakerHouse.fbx";

ModuleRender::ModuleRender() 
	: context(nullptr)
	, RenderModel(nullptr)
{
}

ModuleRender::~ModuleRender()
{
}

// TODO: This function doesn't belong here
static void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
) {
	(void)source; (void)type; (void)id;
	(void)severity; (void)length; (void)userParam;
	fprintf(stderr, "%s\n", message);
	ENGINE_LOG(message);
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		ENGINE_LOG("Aborting...\n");
		abort();
	}
}

bool ModuleRender::Init()
{	
	ENGINE_LOG("Creating Renderer context");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);  // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();

	ENGINE_LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	ENGINE_LOG("Vendor: %s", glGetString(GL_VENDOR));
	ENGINE_LOG("Renderer: %s", glGetString(GL_RENDERER));
	ENGINE_LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	ENGINE_LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Pipeline rasterization configurations
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	
	// Enable the debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

	glEnable(GL_TEXTURE_2D);

	SDL_GetWindowSize(App->window->window, &Width, &Height);
	glViewport(0, 0, Width, Height);

	RenderModel = new Model(bakerHouseModel);
	
	return true;
}

update_status ModuleRender::PreUpdate()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	RenderModel->Draw(App->program->ProgramId, App->camera->GetViewMatrix(), App->camera->GetProjectionMAtrix(), float4x4::identity);

	SDL_Surface* sdlSurface = App->window->ScreenSurface;
	App->ddraw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMAtrix(), sdlSurface->w, sdlSurface->h);

	// Note: Debug draw disables blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	ENGINE_LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);
	
	return true;
}

void ModuleRender::UpdateWindowSize()
{
	SDL_GetWindowSize(App->window->window, &Width, &Height);
	glViewport(0, 0, Width, Height);
}

bool ModuleRender::LoadModule(const char* filePath)
{
	if (RenderModel != nullptr)
	{
		delete RenderModel;
	}
	RenderModel = new Model(filePath);

	return RenderModel->IsValid();
}
