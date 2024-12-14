#pragma once
#include "Module.h"
#include <GL/glew.h>

struct SDL_Texture;
struct SDL_Renderer;
#pragma once
struct SDL_Rect;

struct TextureHandle; //to not have to include opengl in header

class ModuleOpenGL : public Module
{
public:
	ModuleOpenGL();
	virtual ~ModuleOpenGL();

	bool Init();
	update_status PreUpdate(float deltaTime);
	update_status Update(float deltaTime);
	update_status PostUpdate(float deltaTime);
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);
	void* GetContext() const { return context; }


	GLuint LoadTextureToGPU(const wchar_t* filePath);
	
private:
	void* context;
};
