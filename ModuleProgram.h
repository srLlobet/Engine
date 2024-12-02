#pragma once
#include <GL/glew.h> 
#include <GL/gl.h>
#include <memory>

class ModuleProgram
{
public:
	ModuleProgram();

	// Destructor
	virtual ~ModuleProgram();

	static std::unique_ptr<char[]> LoadShaderSource(const char* shader_file_name);

	static unsigned CompileShader(unsigned type, const char* source);

	static unsigned CreateProgram(const char* path_vertex, const char* path_fragment);

public:
	GLuint program;

};


