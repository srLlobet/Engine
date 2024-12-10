#pragma once

#include "Globals.h"

class Application;

class Module
{
public:

	Module()
	{
	}

    virtual ~Module()
    {
    }

	virtual bool Init() 
	{
		return true; 
	}

	virtual update_status PreUpdate(float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float deltaTime)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}
};
