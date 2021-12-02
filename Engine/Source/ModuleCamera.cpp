#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Model.h"

#include "GL/glew.h"
#include "MathGeoLib.h"

static const float DEGTORAD = math::pi / 180.0;
static const float EPSILON = 1e-5;

ModuleCamera::ModuleCamera()
	: AspectRatio(0.0f)
	, HorizontalFovDegree(0.0f)
	, NearDistance(0.0f)
	, FarDistance(0.0f)
	, CameraSpeed(0.5f)
	, RotateSpeed(0.01f)
	, Angle(0.0f)
	, Roll(1.0f, 0.0f, 0.0f)
	, Pitch(0.0f, 1.0f, 0.0f)
	, Yaw(0.0f, 0.0f, 1.0f)
	, LookPosition(float3::zero)
	, Position(float3::zero)
{
}

bool ModuleCamera::Init()
{
    CameraFrustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    SDL_Surface* screenSurface = App->window->ScreenSurface;
    SetAspectRatio(screenSurface->w, screenSurface->h);
    SetHorizontalFovInDegrees(90.0f);
    SetPlaneDistances(0.1f, 100.0f);
    SetPosition(float3(1.0f, 1.0f, 5.0f));
    float3x3 rotation = float3x3::identity;
    CameraFrustum.SetFront(rotation.WorldZ());
    CameraFrustum.SetUp(rotation.WorldY());
    Look(float3(0.0f, 0.0f, 0.0f));
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
    // TODO: Return view matrix from roll, pitch & yaw values
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

const float3& ModuleCamera::GetPosition()
{
    return Position;
}

void ModuleCamera::Rotate(float pitch, float yaw)
{
    if (yaw > EPSILON || yaw < EPSILON)
    {
        // Rotate in Y absolut axis
        Quat rot = Quat::RotateY(yaw);
        CameraFrustum.SetFront(rot.Mul(CameraFrustum.Front()).Normalized());
        CameraFrustum.SetUp(rot.Mul(CameraFrustum.Up()).Normalized());
    }

    if (pitch > EPSILON || pitch < EPSILON)
    {
        // Rotate in X local axis
        Quat rot = Quat::RotateAxisAngle(CameraFrustum.WorldRight(), pitch);
        CameraFrustum.SetUp(rot.Mul(CameraFrustum.Up()).Normalized());
        CameraFrustum.SetFront(rot.Mul(CameraFrustum.Front()).Normalized());
    }
}

void ModuleCamera::SetAspectRatio(unsigned int width, unsigned int height)
{
    AspectRatio = (float)width / (float)height;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFovDegree * DEGTORAD, AspectRatio);
}

float ModuleCamera::GetAspectRatio()
{
    return CameraFrustum.AspectRatio();
}

void ModuleCamera::SetHorizontalFovInDegrees(float fovDegree)
{
    HorizontalFovDegree = fovDegree ;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFovDegree * DEGTORAD, AspectRatio);
}

float ModuleCamera::GetHorizontalFovDegrees() const
{
    return HorizontalFovDegree;
}

void ModuleCamera::Look(const float3& position)
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
    AspectInputs();
}

inline void ModuleCamera::TranslationInputs()
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

inline void ModuleCamera::AspectInputs()
{
    if (App->input->GetKeyboard(SDL_SCANCODE_Q))
    {
        ZoomOutFOV();
    }

    if (App->input->GetKeyboard(SDL_SCANCODE_E))
    {
        ZoomInFOV();
    }
    SetHorizontalFovInDegrees(HorizontalFovDegree);
}

inline void ModuleCamera::RotationInputs()
{
    // TODO: improve calls to application

    // Keyboard
    if (App->input->GetKeyboard(SDL_SCANCODE_UP))
    {
        Rotate(RotateSpeed, 0.0f);
    }
    if (App->input->GetKeyboard(SDL_SCANCODE_DOWN))
    {
        Rotate(-RotateSpeed, 0.0f);
    }
    if (App->input->GetKeyboard(SDL_SCANCODE_LEFT))
    {
        Rotate(0.0f, RotateSpeed);
    }
    if (App->input->GetKeyboard(SDL_SCANCODE_RIGHT))
    {
        Rotate(0.0f, -RotateSpeed);
    }

    // Mouse
    if (App->input->GetMouseButton().button == SDL_BUTTON_RIGHT && App->input->GetMouseButton().state == SDL_PRESSED)
    {
        int mouseMotionX = App->input->GetMouseMotion().X;
        int mouseMotionY = App->input->GetMouseMotion().Y;
        Rotate(-0.01 * (float)mouseMotionY, -0.01 * (float)mouseMotionX);
    }

    // Orbit
    if (App->input->IsModPressed(KMOD_ALT)
        && App->input->GetMouseButton().button == SDL_BUTTON_LEFT 
        && App->input->GetMouseButton().state == SDL_PRESSED)
    {
        float3 moduleOrigin = App->renderer->GetCurrentModel()->GetOrigin();
        App->input->GetMouseMotion().X * RotateSpeed;
        Look(moduleOrigin);
    }
}

void ModuleCamera::ZoomInPosition()
{
    Position += CameraFrustum.Front() * CameraSpeed;
}

void ModuleCamera::ZoomOutPosition()
{
    Position -= CameraFrustum.Front() * CameraSpeed;
}

inline void ModuleCamera::ZoomOutFOV()
{
    if (HorizontalFovDegree >= 120.0f)
    {
        return;
    }
    HorizontalFovDegree += HorizontalFovDegree * RotateSpeed;
}

inline void ModuleCamera::ZoomInFOV()
{
    if (HorizontalFovDegree <= 0.1)
    {
        return;
    }
    HorizontalFovDegree -= HorizontalFovDegree * RotateSpeed;
}

void ModuleCamera::SetPlaneDistances(const float nearDist, const float farDist)
{
    CameraFrustum.SetViewPlaneDistances(NearDistance = nearDist, FarDistance = farDist);
}

void ModuleCamera::SetDefaultValues()
{
    CameraFrustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    SDL_Surface* screenSurface = App->window->ScreenSurface;
    SetAspectRatio(screenSurface->w, screenSurface->h);
    SetHorizontalFovInDegrees(90.0f);
    SetPlaneDistances(0.1f, 100.0f);
    SetPosition(float3(1.0f, 1.0f, 5.0f));
    float3x3 rotation = float3x3::identity;
    CameraFrustum.SetFront(rotation.WorldZ());
    CameraFrustum.SetUp(rotation.WorldY());
    Look(float3(0.0f, 0.0f, 0.0f));
}
