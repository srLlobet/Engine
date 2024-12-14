#pragma once
#include "Module.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	virtual ~ModuleInput();

	bool Init();
	update_status Update(float deltaTime);
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
};