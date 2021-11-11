#include "ModuleProgram.h"
#include <GL/glew.h>
#include <cassert>

const char* FRAGMENT_SHADER_FILE = "C:\\Users\\SoppelsA\\OneDrive - HP Inc\\Documents\\Personal Folder\\Master UPC\\C++Programming\\Homework\\AdvanceCpp\\Engine\\Source\\Shaders\\fragment_triangle.glsl";
const char* VERTEX_SHADER_FILE = "C:\\Users\\SoppelsA\\OneDrive - HP Inc\\Documents\\Personal Folder\\Master UPC\\C++Programming\\Homework\\AdvanceCpp\\Engine\\Source\\Shaders\\vertex_triangle.glsl";
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
			LOG("Log Info: %s", info);
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
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	
	return program_id;
}

ModuleProgram::ModuleProgram() :
	vao(0),
	vertex_id(0),
	fragment_id(0),
	program(0)
{
	VertexPath = VERTEX_SHADER_FILE;
	FragmentPath = FRAGMENT_SHADER_FILE;
}

ModuleProgram::ModuleProgram(std::string& vertex_path, std::string& fragment_path) :
	vao(0),
	vertex_id(0),
	fragment_id(0),
	program(0)
{
	VertexPath = vertex_path;
	FragmentPath = fragment_path;
}

ModuleProgram::ModuleProgram(std::string&& vertex_path, std::string&& fragment_path) :
	vao(0),
	vertex_id(0),
	fragment_id(0),
	program(0)
{
	VertexPath = std::move(vertex_path);
	FragmentPath = std::move(fragment_path);
	vertex_path.clear();
	fragment_path.clear();
}

ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	// Load Source Code & Compile Vertex Shader
	const char* vertexShaderSource = LoadShaderSource(VertexPath.c_str());
	vertex_id = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);

	// Load Source Code & Compile Fragment Shader
	const char* fragmentShaderSource = LoadShaderSource(FragmentPath.c_str());
	fragment_id = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// Link already Compiled Program
	program = CreateProgram(vertex_id, fragment_id);

	// Once is linked it can be destroyed
	glDeleteShader(fragment_id);
	glDeleteShader(vertex_id);
	glGenVertexArrays(1, &vao);

	return true;
}

update_status ModuleProgram::Update()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	
	return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
	glDeleteProgram(program);
	
	return true;
}
