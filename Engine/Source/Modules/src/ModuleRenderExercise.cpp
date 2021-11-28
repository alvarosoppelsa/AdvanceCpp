#include "ModuleRenderExercise.h"
#include "Application.h"
#include "Globals.h"

#include <GL/glew.h>
#include <SDL/include/SDL.h>
#include <cassert>

#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"

ModuleRenderExercise::ModuleRenderExercise() :
	Vbo(0), Ebo(0)
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 640.0, 480.0, 0.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);

	Create_2Triangles_Texture_6Vertices(Vbo);
	//Create_Triangle_NoTexture_3Vertices(Vbo);
	return true;
}

bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO(Vbo);
	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	glUseProgram(App->program->ProgramId);
	Render_2Triangles_Texture_6Vertices();

	//Render_Triangle_Transformation();
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleRenderExercise::Create_Triangle_NoTexture_3Vertices(unsigned int vbo)
{
	float buffer[] =
	{
		-1.0f, -1.0f, 0.0f,   // ← v0 pos
		 1.0f, -1.0f, 0.0f,   // ← v1 pos
		 0.0f,  1.0f, 0.0f,   // ← v2 pos
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), buffer, GL_STATIC_DRAW);
}

void ModuleRenderExercise::Render_Triangle_Transformation(unsigned int vbo)
{

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	

	glDrawArrays(GL_TRIANGLES, 0, 3);
	assert(glGetError() == GL_NO_ERROR);

	App->ddraw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMAtrix(), App->renderer->Width, App->renderer->Height);
}

void ModuleRenderExercise::Create_2Triangles_Texture_6Vertices(unsigned int vbo)
{
	float buffer[] = 
	{
		-1.0f, -1.0f, 0.0f,   // ← v0 pos
		 1.0f, -1.0f, 0.0f,   // ← v1 pos
		 1.0f,  1.0f, 0.0f,   // ← v2 pos

		 1.0f,  1.0f, 0.0f,   // ← v2 pos
		-1.0f,  1.0f, 0.0f,   // ← v3 pos
		-1.0f, -1.0f, 0.0f,   // ← v0 pos

		 0.0f, 0.0f,         // ← v0 texcoord
		 1.0f, 0.0f,         // ← v1 texcoord
		 1.0f, 1.0f,         // ← v2 texcoord

		 1.0f, 1.0f,         // ← v2 texcoord
		 0.0f, 1.0f,         // ← v3 texcoord
		 0.0f, 0.0f,         // ← v0 texcoord

	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, (6 * 3 + 6 * 2) * sizeof(float), buffer, GL_STATIC_DRAW);

}

void ModuleRenderExercise::Render_2Triangles_Texture_6Vertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0/*3 * sizeof(float)*/, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0/*2 * sizeof(float)*/, (void*)(sizeof(float) * 6 * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &Ebo);
	assert(glGetError() == GL_NO_ERROR);

	//App->ddraw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMAtrix(), App->renderer->Width, App->renderer->Height);

}

void ModuleRenderExercise::Create_QuadElements_NoTexture_4Vertices(unsigned int vbo, unsigned int ebo)
{
	float vertices[] =
	{
		// position
		-0.5f, -0.5f, 0.0f,	// 0
		 0.5f, -0.5f, 0.0f, // 1
		 0.5f,  0.5f, 0.0f, // 2
		-0.5f,  0.5f, 0.0f,	// 3
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

void ModuleRenderExercise::DestroyVBO(unsigned int vbo)
{
	glDeleteBuffers(1, &vbo);
}