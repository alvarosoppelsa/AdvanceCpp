#pragma once

#include "Module.h"
#include <MathGeoLib.h>
#include <string>

class ModuleProgram : public Module
{

public:
	ModuleProgram();
	ModuleProgram(std::string& vertexPath, std::string& fragmentPath);
	~ModuleProgram() = default;
	
	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	int GetProgramId() const { return ProgramId; }

private:
	unsigned int VertexId;
	unsigned int FragmentId;
	unsigned int ProgramId;

	std::string VertexShaderPath;
	std::string FragmentShaderPath;

	char* LoadShaderSource(const char* shader_file_name);
	unsigned int CompileShader(unsigned type, const char* source);
	unsigned int CreateProgram(unsigned vtx_shader, unsigned frg_shader);

};

