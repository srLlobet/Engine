#pragma once
#include "Module.h"
#include "DirectXTex.h"

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	~ModuleTexture();

	DirectX::ScratchImage LoadImage(const wchar_t* imageFileName);

};

