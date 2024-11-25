#pragma once
#include "Module.h"

class ModuleEditor : public Module
{
public:

	ModuleEditor();

	// Destructor
	virtual ~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool cleanup();

};