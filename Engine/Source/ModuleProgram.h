#pragma once

#include "Module.h"
#include <string>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	ModuleProgram(std::string& vertex_path, std::string& fragment_path);
	ModuleProgram(std::string&& vertex_path, std::string&& fragment_path);
	~ModuleProgram();
	
	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;


private:
	unsigned int vao;
	unsigned int vertex_id;
	unsigned int fragment_id;
	unsigned int program;
	std::string VertexPath;
	std::string FragmentPath;

	char* LoadShaderSource(const char* shader_file_name);
	unsigned int CompileShader(unsigned type, const char* source);
	unsigned int CreateProgram(unsigned vtx_shader, unsigned frg_shader);

};

