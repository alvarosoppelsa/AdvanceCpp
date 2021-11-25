#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMAtrix();

	void SetPosition(const float3& position);
	void Rotate(float pitch, float yaw);
	void SetAspectRatio(unsigned int screen_width, unsigned int screen_height);
	void SetHorizontalFov(float fov_deg);
	void LookAt(const float3& position);
	void CameraInputs();
	void SetPlaneDistances(const float nearDist, const float farDist);
	void WindowResized(unsigned int width, unsigned int height);
private:
	Frustum CameraFrustum;

	bool Locked = false;
	float AspectRatio;
	float HorizontalFov;
	float NearDistance;
	float FarDistance;
	float CameraSpeed;
	float3 LookPosition;
	float3 Position;
};

