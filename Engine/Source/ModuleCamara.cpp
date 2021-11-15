#include "ModuleCamara.h"
#include "GL/glew.h"

bool ModuleCamara::Init()
{
    return true;
}

update_status ModuleCamara::PreUpdate()
{


    return UPDATE_CONTINUE;
}

update_status ModuleCamara::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleCamara::CleanUp()
{
    return true;
}

void ModuleCamara::SetFOV()
{
}

void ModuleCamara::SetAspectRatio()
{
}

void ModuleCamara::SetPlaneDistances()
{
}

void ModuleCamara::GetProjectionMatrix()
{
}

void ModuleCamara::GetViewMatrix()
{
}
