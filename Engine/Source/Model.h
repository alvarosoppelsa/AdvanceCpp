#pragma once

#include "Mesh.h"

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(const char* file);

    void Draw(const unsigned int programId, const float4x4& view, const float4x4& proj, const float4x4& model);

	bool IsValid() { return (!Directory.empty() && Meshes.size() != 0 && TexturesLoaded.size() != 0); }
    const std::vector<Mesh>& GetMeshes() const { return Meshes; }
    const std::string& GetDirectory() const { return Directory; }

	const float3& GetOrigin() const { return Position; }
    void SetOrigin(const float3& position) { Position = position; }

private:
    // model data
    std::vector<Mesh> Meshes;
    std::string Directory;
    std::vector<Texture> TexturesLoaded;
    float3 Position;

    void Load(const char* file);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    int TextureFromFile(const char* path, const std::string& directory);
};

