#include "ModuleRenderExercise.h"
#include "Application.h"
#include "Globals.h"

#include <GL/glew.h>
#include <cassert>

#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"

ModuleRenderExercise::ModuleRenderExercise() :
	Vbo(0), Ebo(0)
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	//Create_2Triangles_Texture_6Vertices(Vbo);
	Create_Triangle_NoTexture_3Vertices(Vbo);
	return true;
}

bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO(Vbo);
	return true;
}

update_status ModuleRenderExercise::Update()
{
	//Render_2Triangles_Texture_6Vertices();

	Render_Triangle_Transformation();
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

void ModuleRenderExercise::Render_Triangle_Transformation()
{
	//unsigned int prog = App->program->program;

	//// TODO: retrieve model view and projection
	//Frustum frustum;
	////frustum.type = FrustumType::PerspectiveFrustum;
	//frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumRightHanded);
	////frustum.pos = float3::zero;
	//frustum.SetPos(float3(0.0f, 0.1f, 0.0f));
	////frustum.front = -float3::unitZ;
	//frustum.SetFront(-float3::unitZ);
	////frustum.up = float3::unitY;
	//frustum.SetUp(float3::unitY);
	////frustum.nearPlaneDistance = 0.1f;
	////frustum.farPlaneDistance = 100.0f;
	//frustum.SetViewPlaneDistances(0.1f, 100.0f);

	//float verticalFov = math::pi / 4.0f;
	//float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
	//float horizontalFov = 2.f * atanf(tanf(verticalFov * 0.5f) * aspectRatio);
	//frustum.SetVerticalFovAndAspectRatio(verticalFov, aspectRatio);
	//frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
	//

	//Proj  = frustum.ProjectionMatrix();
	//View  = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));
	//Model = float4x4::LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY, float3::unitY);

	//Proj.Transpose();
	//Model.Transpose();
	//View.Transpose();
	//GLfloat matrix = 1.0f;
	//glUseProgram(prog);
	//glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_TRUE, &matrix);
	//glUniformMatrix4fv(glGetUniformLocation(prog, "view"), 1, GL_TRUE, &matrix);
	//glUniformMatrix4fv(glGetUniformLocation(prog, "proj"), 1, GL_TRUE, &matrix);
	//
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	assert(glGetError() == GL_NO_ERROR);
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