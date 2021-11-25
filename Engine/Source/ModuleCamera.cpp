#include "ModuleCamera.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"

static const float DEGTORAD = math::pi / 180.0;

ModuleCamera::ModuleCamera()
	: Locked(false)
	, AspectRatio(0.0f)
	, HorizontalFov(0.0f)
	, NearDistance(0.0f)
	, FarDistance(0.0f)
	, CameraSpeed(5.0f)
	, LookPosition(float3::zero)
	, Position(float3::zero)
{
}

bool ModuleCamera::Init()
{
    CameraFrustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    SDL_Surface* screenSurface = App->window->ScreenSurface;
    SetAspectRatio(screenSurface->w, screenSurface->h);
    SetHorizontalFov(90.0f);
    SetPlaneDistances(0.1f, 100.0f);
    SetPosition(float3(1.0f, 1.0f, 5.0f));
    float3x3 rotation = float3x3::identity;
    CameraFrustum.SetFront(rotation.WorldZ());
    CameraFrustum.SetUp(rotation.WorldY());
    LookAt(float3(0.0f, 0.0f, 0.0f));
    return true;
}

update_status ModuleCamera::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
    CameraInputs();
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return true;
}

float4x4 ModuleCamera::GetViewMatrix()
{
    return float4x4(CameraFrustum.ViewMatrix());
}

float4x4 ModuleCamera::GetProjectionMAtrix()
{
    return CameraFrustum.ProjectionMatrix();
}

void ModuleCamera::SetPosition(const float3& position)
{
    CameraFrustum.SetPos(Position = position);
}

void ModuleCamera::Rotate(float pitch, float yaw)
{
}

void ModuleCamera::SetAspectRatio(unsigned int width, unsigned int height)
{
    AspectRatio = (float)width / (float)height;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFov, AspectRatio);
}

void ModuleCamera::SetHorizontalFov(float fovDegree)
{
    HorizontalFov = fovDegree * DEGTORAD;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFov, AspectRatio);
}

void ModuleCamera::LookAt(const float3& position)
{
    float3 direction = LookPosition - CameraFrustum.Pos();
    float3x3 lookDir = float3x3::LookAt(CameraFrustum.Front(), direction.Normalized(), CameraFrustum.Up(), float3::unitY);

	CameraFrustum.SetFront(lookDir.MulDir(CameraFrustum.Front()).Normalized());
    CameraFrustum.SetUp(lookDir.MulDir(CameraFrustum.Up()).Normalized());
}

void ModuleCamera::CameraInputs()
{
    TranslationInputs();
    RotationInputs();
}

void ModuleCamera::TranslationInputs()
{
    if (App->input->GetKeyboard(SDL_SCANCODE_W))
    {
        Position += CameraFrustum.Front() * CameraSpeed;
    }

    if (App->input->GetKeyboard(SDL_SCANCODE_S))
    {
        Position -= CameraFrustum.Front() * CameraSpeed;
    }

    if (App->input->GetKeyboard(SDL_SCANCODE_D))
    {
        Position += CameraFrustum.WorldRight() * CameraSpeed;
    }

    if (App->input->GetKeyboard(SDL_SCANCODE_A))
    {
        Position -= CameraFrustum.WorldRight() * CameraSpeed;
    }

    SetPosition(Position);
}

void ModuleCamera::RotationInputs()
{
    if (App->input->GetKeyboard(SDL_SCANCODE_Q))
    {
        HorizontalFov += HorizontalFov * CameraSpeed;
    }

    if (App->input->GetKeyboard(SDL_SCANCODE_E))
    {
        HorizontalFov -= HorizontalFov * CameraSpeed;
    }
    SetHorizontalFov(HorizontalFov);
}

void ModuleCamera::SetPlaneDistances(const float nearDist, const float farDist)
{
    CameraFrustum.SetViewPlaneDistances(NearDistance = nearDist, FarDistance = farDist);
}

void ModuleCamera::WindowResized(unsigned int width, unsigned int height)
{
    SetAspectRatio(width, height);
}
