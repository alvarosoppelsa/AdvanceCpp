#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "MathGeoLib.h"
#include "Performance.h"

enum class MoveType
{
	TRANSLATION = 0,
	ROTATION,
	ZOOM_POS,
	ZOOM_FOV,
	ORBIT
};

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
	float4x4 GetProjectionMatrix();

	void SetPosition(const float3& position);
	const float3& GetPosition() const;
	void Rotate(float3 rotation);

	void SetAspectRatio(unsigned int width, unsigned int height);
	float GetAspectRatio();
	void SetHorizontalFovInDegrees(float fov_deg);
	float GetHorizontalFovDegrees() const;
	void Look(const float3& position);
	void LookModule();

	void SetPlaneDistances(const float nearDist, const float farDist);
	void SetDefaultValues();

	void ZoomInPosition();
	void ZoomOutPosition();

	float GetMoveSpeed() const { return Speed; };
	float GetZoomPosSpeed() const { return ZoomPosSpeed; };
	float GetRotationSpeed() const { return RotationSpeed; };
	float GetOrbitSpeed() const { return OrbitSpeed; };

	void SetMoveSpeed(const float speed) { Speed = speed; };
	void SetZoomPosSpeed(const float speed) { ZoomPosSpeed = speed; };
	void SetRotationSpeed(const float speed) { RotationSpeed = speed; };
	void SetOrbitSpeed(const float speed) { OrbitSpeed = speed; };

private:
	Frustum CameraFrustum;
	// Projection
	float AspectRatio;
	float HorizontalFovDegree;
	float NearDistance;
	float FarDistance;
	// Rotation
	float Roll;
	float Pitch;
	float Yaw;
	void UpdateRotationMatrix();
	// Speed
	float Speed;
	float RotationSpeed;
	float ZoomPosSpeed;
	float ZoomFovSpeed;
	float OrbitSpeed;
	//Matrices
	float4x4 RotationMatrix;
	float4x4 TranslationMatrix;
	// Translation
	float3 LookPosition;
	float3 Position;
	// Inputs
	void CameraInputs();
	void TranslationInputs();
	void AspectInputs();
	void RotationInputs();

	float GetSpeed(MoveType type = MoveType::TRANSLATION) const;
	void ZoomOutFOV();
	void ZoomInFOV();

	float3 GetUp() const;
	float3 GetFront() const;
	float3 GetDirection() const;
	float3 GetRight() const;

	void SetUp(float3 new_up);
	void SetFront(float3 new_front);
	void SetDirection(float3 new_direction);
	void SetRight(float3 new_right);
};

