#include "ModuleCamera.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleProgram.h"

bool ModuleCamera::Init()
{
    return true;
}

update_status ModuleCamera::Update()
{
    GLuint program = App->program->program;
    Frustum frustum;
    frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum.SetViewPlaneDistances(0.1f, 200.0f);
    frustum.SetHorizontalFovAndAspectRatio(math::pi / 3, 1.3f); // 90 degrees
    frustum.SetPos(float3(0.0f, 0.0f, 0.0f));
    frustum.SetFront(float3::unitZ);
    frustum.SetUp(float3::unitY);
    float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); // < --Important to transpose!

	//Send the frustum projection matrix to OpenGL
    // direct mode would be:
	//glMatrixMode(GL_PROJECTION);
    //glLoadMatrixf(*projectionGL.v);

    frustum.SetPos(float3(0.0f, 0.25f, 0.0f));
    float3x3 rotationMatrix = float3x3(float3(0.3f, 0.2f, 0.7f), float3(0.2f, 0.2f, 0.2f), float3(0.5f, 0.5f, 0.5f)); // = some rotation value (or LookAt matrix)
    frustum.SetFront(rotationMatrix.WorldX());
    frustum.SetUp(rotationMatrix.WorldY());

    //Send the frustum view matrix to OpenGL
    // direct mode would be:
    /*float4x4 viewGL = float4x4(frustum.ViewMatrix()).Transposed();
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&viewGL[4][4]);*/

    //float4x4 translationMatrix(float4(1.0f,0.0f,0.0f,0.0f), float4(0.0f, 1.0f, 0.0f, 0.0f), float4(0.0f, 0.0f, 1.0f, 0.0f), float4(0.0f, 0.0f, increment, 1.0f));
    // Send to uniforms matrix
	//glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &viewGL[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projectionGL[0][0]);

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PreUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return true;
}
