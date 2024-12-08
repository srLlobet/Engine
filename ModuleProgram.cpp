#include "ModuleProgram.h"
#include "ModuleOpenGL.h"
#include "Globals.h"
#include "Logger.h"
#include <fstream> 


ModuleProgram::ModuleProgram()
{

}

ModuleProgram::~ModuleProgram()
{

}


std::unique_ptr<char[]> ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	FILE* f = nullptr;

	//protections
	LOG("Attempting to open shader file: %s", shader_file_name);

	if (fopen_s(&f, shader_file_name, "rb") != 0 || f == nullptr) {
		return nullptr;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return nullptr;
	}
	int fsize = ftell(f);
	if (fsize == -1) {
		fclose(f);
		return nullptr;
	}

	std::unique_ptr<char[]> data(new char[fsize + 1]);

	fseek(f, 0, SEEK_SET);

	if (fread(data.get(), 1, fsize, f) != fsize) {
		fclose(f);
		return nullptr;
	}

	data[fsize] = '\0';
	fclose(f);

	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
	//compile shader
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);

	//checks
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			std::unique_ptr<char[]> info(new char[len]);
			glGetShaderInfoLog(shader_id, len, &written, info.get());
			LOG("Log Info: %s", info.get());
			
		}
	}
	return shader_id;

}

unsigned ModuleProgram::CreateProgram(const char* path_vertex, const char* path_fragment)
{
	std::unique_ptr<char[]> vertex = LoadShaderSource(path_vertex);
	if (!vertex) {
		Logger::Instance().LOGS("Failed to load vertex shader source");
		return 0;
	}

	std::unique_ptr<char[]> fragment = LoadShaderSource(path_fragment);
	if (!fragment) {
		Logger::Instance().LOGS("Failed to load fragment shader source");
		return 0;
	}

	unsigned vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex.get());
	if (vertex_shader == 0) {
		Logger::Instance().LOGS("Vertex shader compilation failed");
		return 0;
	}

	unsigned fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment.get());
	if (fragment_shader == 0) {
		Logger::Instance().LOGS("Fragment shader compilation failed");
		glDeleteShader(fragment_shader);  // Clean up if there's an error
		return 0;
	}

	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
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
			std::unique_ptr<char[]> info(new char[len]);
			glGetProgramInfoLog(program_id, len, &written, info.get());
			LOG("Program Log Info: %s", info.get());
		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteProgram(program_id);
		return 0;
	}
	glDetachShader(program_id, vertex_shader);
	glDetachShader(program_id, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program_id;

}


