#pragma once
#include "Module.h"
class ModuleModel : public Module
{
public:

	ModuleModel();
	virtual ~ModuleModel();

	bool Init();
	void Load(const char* assetFileName);
	void LoadFromDragAndDrop(const char* assetFileName);
private:
	float scalex, scaley, scalez;
};

