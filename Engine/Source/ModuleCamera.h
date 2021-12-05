#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "MathGeoLib.h"
#include "Performance.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMAtrix();

	void SetPosition(const float3& position);
	const float3& GetPosition() const;
	void Rotate(float pitch, float yaw, float roll);

	void SetAspectRatio(unsigned int width, unsigned int height);
	float GetAspectRatio();
	void SetHorizontalFovInDegrees(float fov_deg);
	float GetHorizontalFovDegrees() const;
	void Look(const float3& position);

	void SetPlaneDistances(const float nearDist, const float farDist);
	void SetDefaultValues();

	void ZoomInPosition();
	void ZoomOutPosition();

private:
	Frustum CameraFrustum;

	float AspectRatio;
	float HorizontalFovDegree;
	float NearDistance;
	float FarDistance;
	float Speed;
	float Angle;

	float Roll;
	float Pitch;
	float Yaw;

	float3 LookPosition;
	float3 Position;

	void CameraInputs();
	void TranslationInputs();
	void AspectInputs();
	void RotationInputs();

	float GetSpeed() const;
	void ZoomOutFOV();
	void ZoomInFOV();
};

