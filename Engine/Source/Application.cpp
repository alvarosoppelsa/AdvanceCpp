#pragma once

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleRenderExercise.h"
#include "ModuleCamara.h"

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window	= new ModuleWindow());
	modules.push_back(renderer	= new ModuleRender());
	modules.push_back(input		= new ModuleInput());
	modules.push_back(editor	= new ModuleEditor());
	//modules.push_back(program	= new ModuleProgram());
	modules.push_back(camera    = new ModuleCamera());
	modules.push_back(ddraw     = new ModuleDebugDraw());
	//modules.push_back(texture	= new ModuleTexture());
	//modules.push_back(exercise	= new ModuleRenderExercise());

}

Application::~Application()
{
	for(std::list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (std::list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
	{
		ret = (*it)->CleanUp();
		delete* it;
		*it = nullptr;
	}

	return ret;
}
