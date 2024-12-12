
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercise.h"
#include "ModuleTexture.h"
#include "DirectXTex.h"
#include "Logger.h"
#include "SDL.h"

ModuleOpenGL::ModuleOpenGL()
{

}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{
}

// Called before render is available
bool ModuleOpenGL::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->GetWindow()->window);

	GLenum err = glewInit();

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	GLuint textureID = LoadTextureToGPU(L"Test-image-Baboon.png");
	return true;
}

update_status ModuleOpenGL::PreUpdate(float deltaTime)
{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update(float deltaTime)
{

	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate(float deltaTime)
{
	SDL_GL_SwapWindow(App->GetWindow()->window);
	return UPDATE_CONTINUE;
}


bool ModuleOpenGL::CleanUp()
{
	LOG("Destroying renderer");

	//glDeleteTextures(1, &textureID);
	SDL_GL_DeleteContext(context);

	context = nullptr;

	SDL_DestroyWindow(App->GetWindow()->window);
	App->GetWindow()->window = nullptr;


	SDL_Quit();
	return true;
}

//handles opengl operation
void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
	glViewport(0, 0, width, height);  // Update the OpenGL viewport

	App->GetCamera()->RecalculateHorizontalFov(static_cast<float>(width) / height);
	App->GetRenderExercise()->UpdateProjectionMatrix();
}

GLuint ModuleOpenGL::LoadTextureToGPU(const wchar_t* filePath) {

	DirectX::ScratchImage image = App->GetTexture()->LoadImage(filePath);

	const DirectX::TexMetadata& metadata = image.GetMetadata();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Wrap mode S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // Wrap mode T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Minification filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Magnification filter

	GLenum internalFormat, format, type;

	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
	if (metadata.mipLevels > 1) {

	}
	else {
		glTexImage2D(
			GL_TEXTURE_2D,
			0, // level of detail, higher 0
			internalFormat, // Internal format
			metadata.width, // Width
			metadata.height, // Height
			0, // border size (0)
			format, // data format
			GL_UNSIGNED_BYTE, // Type
			image.GetPixels() // Pointer to the pixel data
		);

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}