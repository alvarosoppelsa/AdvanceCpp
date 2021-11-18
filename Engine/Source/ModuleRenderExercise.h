#pragma once
#include "Module.h"
class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool CleanUp();
	update_status Update();

private:
	void CreateTriangleVBO(unsigned int Vbo);
	void CreateSquareVBO(unsigned int vbo, unsigned int ebo);
	void RenderVBO(unsigned int vbo, unsigned int ebo);
	void DestroyVBO(unsigned int vbo);
	unsigned int Vbo;
	unsigned int Ebo;
};

