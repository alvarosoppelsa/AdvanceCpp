#pragma once
#include <windows.h>
#include <stdio.h>

#define ENGINE_LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Game Engine"
#define MY_REPO "https://github.com/alvarosoppelsa/AdvanceCpp/tree/master/Engine"
#define LIBRARIES_USED "SDL 2.0.16\nGLEW 2.1.0\nDear ImGui 1.86\nDevIL 1.8.0"

// Shaders ----------------
static const char* FRAGMENT_SHADER_FILE = "..\\Source\\Shaders\\FragmentShaderWithUniforms.glsl";
static const char* VERTEX_SHADER_FILE = "..\\Source\\Shaders\\VertexShaderWithUniforms.glsl";

// Init Modules -----------
static const char* BakerHouse = ".\\Resources\\Models\\BakerHouse.fbx";
static const char* DefaultTexturePath = ".\\Resources\\Textures";