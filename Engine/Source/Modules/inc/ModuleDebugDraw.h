#ifndef _MODULE_DEBUGDRAW_H_
#define _MODULE_DEBUGDRAW_H_

#include "Module.h"

#include "Math/float4x4.h"

class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

public:

    ModuleDebugDraw();
    ~ModuleDebugDraw();

	bool            Init() override;
	update_status   PreUpdate() override;
	update_status   Update() override;
	update_status   PostUpdate() override;
	bool            CleanUp() override;

    void            Draw(const float4x4& view, const float4x4& proj, unsigned width, unsigned height);
private:

    static DDRenderInterfaceCoreGL* implementation;
	int GridSize = 500;
	float GizmoSize = 2.0f;
	float GizmoArrow = 0.2f;
};

#endif /* _MODULE_DEBUGDRAW_H_ */
