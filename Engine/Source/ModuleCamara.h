#pragma once

#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleCamara : public Module
{
public:
	// Common Module methods
	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	//Specific methods
	void SetFOV();				// … should set the horizontal FOV keeping the aspect ratio
	void SetAspectRatio();		// … should change the vertical FOV to meet the new aspect ratio.
	void SetPlaneDistances();	// / Position() / Orientation() / LookAt(x, y, z)
	void GetProjectionMatrix(); // OpenGL matrix order is different from default MathGeoLib!Math info here
	void GetViewMatrix();
private:
	Frustum frustum;
};

