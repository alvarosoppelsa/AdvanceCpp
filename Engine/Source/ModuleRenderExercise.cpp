#include "ModuleRenderExercise.h"
#include <GL/glew.h>
#include <cassert>

ModuleRenderExercise::ModuleRenderExercise() :
	Vbo(0)
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	CreateTriangleVBO(Vbo);
	return true;
}

bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO(Vbo);
	return true;
}

update_status ModuleRenderExercise::Update()
{
	RenderVBO(Vbo);
	return UPDATE_CONTINUE;
}

void ModuleRenderExercise::CreateTriangleVBO(unsigned int vbo)
{
	float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void ModuleRenderExercise::RenderVBO(unsigned int vbo)
{
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
	assert(glGetError() == GL_NO_ERROR);
}

void ModuleRenderExercise::DestroyVBO(unsigned int vbo)
{
	glDeleteBuffers(1, &vbo);
}