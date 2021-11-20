#include "ModuleRenderExercise.h"
#include <GL/glew.h>
#include <cassert>

ModuleRenderExercise::ModuleRenderExercise() :
	Vbo(0), Ebo(0)
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	//CreateSquareVBO(Vbo, Ebo);
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
	float buffer[] = 
	{
		-1.0f, -1.0f, 0.0f,   // ← v0 pos
		 1.0f, -1.0f, 0.0f,   // ← v1 pos
		 1.0f,  1.0f, 0.0f,   // ← v2 pos

		 1.0f,  1.0f, 0.0f,   // ← v2 pos
		-1.0f,  1.0f, 0.0f,   // ← v3 pos
		-1.0f, -1.0f, 0.0f,   // ← v0 pos

		 1.0f, 0.0f,         // ← v1 texcoord
		 0.0f, 0.0f,         // ← v0 texcoord
		 0.5f, 1.0f,         // ← v2 texcoord
	};


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, (6 * 3 + 3 * 2) * sizeof(float), buffer, GL_STATIC_DRAW);
}

void ModuleRenderExercise::CreateSquareVBO(unsigned int vbo, unsigned int ebo)
{
	float vertices[] =
	{
		// position
		-0.5f, -0.5f, 0.0f,	// 0
		 0.5f, -0.5f, 0.0f, // 1
		 0.5f,  0.5f, 0.0f, // 2
		-0.5f,  0.5f, 0.0f,	// 3

		//texture
		//0.0f, 0.0f, // ← v0 texcoord
		//1.0f, 0.0f, // ← v1 texcoord
		//0.5f, 1.0f  // ← v2 texcoord
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void ModuleRenderExercise::RenderVBO(unsigned int vbo)
{
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 6 * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &Ebo);
	assert(glGetError() == GL_NO_ERROR);
}

void ModuleRenderExercise::DestroyVBO(unsigned int vbo)
{
	glDeleteBuffers(1, &vbo);
}