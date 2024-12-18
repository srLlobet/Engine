#pragma once
#include "Module.h"
#include "DirectXTex.h"

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	virtual ~ModuleTexture();

	bool Init();
	bool CleanUp();

	DirectX::ScratchImage LoadImage(const wchar_t* imageFileName);

};

