#pragma once
#include "Module.h"
#include "Math/float4x4.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init() override;
	bool CleanUp() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

private:
	void Create_Triangle_NoTexture_3Vertices(unsigned int vbo);
	void Render_Triangle_Transformation(unsigned int vbo);

	void Create_2Triangles_Texture_6Vertices(unsigned int vbo);
	void Render_2Triangles_Texture_6Vertices();

	void Create_QuadElements_NoTexture_4Vertices(unsigned int vbo, unsigned int ebo);
	void DestroyVBO(unsigned int vbo);

	unsigned int Vbo;
	unsigned int Ebo;

	float4x4 Proj;
	float4x4 Model;
	float4x4 View;
};

