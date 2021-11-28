#include "Model.h"
#include "Globals.h"

#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

Model::Model()
{
}

void Model::Load(const char* file)
{
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		ENGINE_LOG("Model %s load succesfully", file);
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		ENGINE_LOG("Error loading %s: %s", file, aiGetErrorString());
	}
}
