#include "ModuleProgram.h"
#include "Globals.h"
#include <GL/glew.h>
#include <cassert>
#include "IL/il.h"

ModuleProgram::ModuleProgram()
	: ProgramId(0)
	, VertexId(0)
	, FragmentId(0)
{
	VertexShaderPath = VERTEX_SHADER_FILE;
	FragmentShaderPath = FRAGMENT_SHADER_FILE;
}

ModuleProgram::ModuleProgram(std::string& vertex_path, std::string& fragment_path)
	: ProgramId(0)
	, VertexId(0)
	, FragmentId(0)
{
	VertexShaderPath = vertex_path;
	FragmentShaderPath = fragment_path;
}

bool ModuleProgram::Init()
{
	// Load Source Code & Compile Vertex Shader
	const char* vertexShaderSource = LoadShaderSource(VertexShaderPath.c_str());
	VertexId = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);

	// Load Source Code & Compile Fragment Shader
	const char* fragmentShaderSource = LoadShaderSource(FragmentShaderPath.c_str());
	FragmentId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// Link already Compiled Program
	ProgramId = CreateProgram(VertexId, FragmentId);

	glUseProgram(ProgramId);

	// Once is linked it can be destroyed
	glDeleteShader(FragmentId);
	glDeleteShader(VertexId);

	return true;
}

update_status ModuleProgram::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleProgram::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
	glDeleteProgram(ProgramId);

	return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, shader_file_name, "rb");
	assert(!error);
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	
	return data;
}

unsigned int ModuleProgram::CompileShader(unsigned type, const char* source)
{
	unsigned int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (!res)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			ENGINE_LOG("Log Info: %s", info);
			free(info);
		}
	}
	
	return shader_id;
}

unsigned int ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program_id, len, &written, info);
			ENGINE_LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	
	return program_id;
}

