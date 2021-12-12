#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class Model;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();


	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void UpdateWindowSize(int width, int height);
	bool LoadModule(const char* filePath);
	const Model* GetCurrentModel() const { return RenderModel; }
	void* GetContext() const
	{
		assert(Context != nullptr);
		return Context;
	}
	
	// Lighting
	const float3& GetLightPosition() const { return LightPosition; }
	void SetLightPosition(const float3& lightPos) { LightPosition = lightPos; }	
	const float3& GetLightColor() const { return LightColor; }
	void SetLightColor(const float3& lightColor) { LightColor = lightColor; }	
	const float GetDiffuseLightIntensity() const { return DiffuseLightIntensity; }
	void SetDiffuseLightIntensity(const float intensity) { DiffuseLightIntensity = intensity; }
	const float GetSpecularLightIntensity() const { return SpecularLightIntensity; }
	void SetSpecularLightIntensity(const float intensity) { SpecularLightIntensity = intensity; }
	const float GetAmbientLightIntensity() const { return AmbientLightIntensity; }
	void SetAmbientLightIntensity(const float intensity) { AmbientLightIntensity = intensity; }

private:
	int Width = 0;
	int Height = 0;
	Model* RenderModel;
	void* Context;
	float3 LightPosition;
	float3 LightColor;
	float DiffuseLightIntensity;
	float SpecularLightIntensity;
	float AmbientLightIntensity;
};
