#pragma once

#include "Module.h"
#include "Globals.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera() = default;
	~ModuleCamera() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;
};

