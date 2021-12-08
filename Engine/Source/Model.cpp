#include "Model.h"

#include "Globals.h"
#include "AssimpLogger.h"
#include "GL/glew.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "Math/float3.h"
#include <assimp/DefaultLogger.hpp>
#include <algorithm>

Model::Model(const char* file)
	: Position(0.0f, 0.0f, 0.0f)
{
    // Create a logger instance 
    DefaultLogger::create("", Logger::VERBOSE);

    // Select the kinds of messages you want to receive on this log stream
    const unsigned int severity = 
        Assimp::Logger::Debugging | 
    	Assimp::Logger::Info | 
        Assimp::Logger::Err | 
        Assimp::Logger::Warn;

    // Attaching it to the default logger
    Assimp::DefaultLogger::get()->attachStream(new AssimpLogger(), severity);
	Load(file);
}

Model::~Model()
{
    DefaultLogger::kill();
}

/*
 * OTHER ASSIMP POSTPROCESS USEFULL OPTIONS ARE:
 * aiProcess_GenNormals
 * aiProcess_SplitLargeMeshes
 * aiProcess_OptimizeMeshes
*/
void Model::Load(const char* file)
{
    ENGINE_LOG("Loading Module: %s", file);
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		ENGINE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
		return;
	}
	std::string path = file;
	Directory = path.substr(0, path.find_last_of('\\'));

    ENGINE_LOG("Scene Summary");
    ENGINE_LOG("Meshes: %d", scene->mNumMeshes);
    ENGINE_LOG("Materials: %d", scene->mNumMaterials);
    ENGINE_LOG("Textures: %d", scene->mNumTextures);
    ENGINE_LOG("Cameras: %d", scene->mNumCameras);
    ENGINE_LOG("Animations: %d", scene->mNumAnimations);
    ENGINE_LOG("Lights: %d", scene->mNumLights);

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Meshes.push_back(ProcessMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Store the first values to be able to compare them later
    OBB.xBounds.min = mesh->mVertices[0].x;
    OBB.xBounds.max = mesh->mVertices[0].x;
    OBB.yBounds.min = mesh->mVertices[0].y;
    OBB.yBounds.max = mesh->mVertices[0].y;
    OBB.zBounds.min = mesh->mVertices[0].z;
    OBB.zBounds.max = mesh->mVertices[0].z;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        float3 vector;

        // Position
    	vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
         
        OBB.xBounds.min = std::min(OBB.xBounds.min, vector.x);
        OBB.xBounds.max = std::max(OBB.xBounds.max, vector.x);
        OBB.yBounds.min = std::min(OBB.yBounds.min, vector.y);
        OBB.yBounds.max = std::max(OBB.yBounds.max, vector.y);
        OBB.zBounds.min = std::min(OBB.zBounds.min, vector.z);
        OBB.zBounds.max = std::max(OBB.zBounds.max, vector.z);

        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // Texture coords (Mesh couln'd have any)
        if (mesh->mTextureCoords[0])
        {
            float2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = float2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // Diffuse
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // Specular
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        //Check if the texture has already loaded
        for (unsigned int j = 0; j < TexturesLoaded.size(); j++)
        {
            if (std::strcmp(TexturesLoaded[j].Path.data(), str.C_Str()) == 0)
            {
                textures.push_back(TexturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (skip)
        {
            continue;
        }
        // if texture hasn't been loaded already, load it
        Texture texture;
        const int texId = TextureFromFile(str.C_Str(), Directory);
        if (texId < 0)
        {
            ENGINE_LOG("Cannot Load Texture: %s", str.C_Str());
            continue;
        }
        texture.Id = (unsigned)texId;
        texture.Type = typeName;
        texture.Path = str.C_Str();
        textures.push_back(texture);
        TexturesLoaded.push_back(texture); // add to loaded textures
    }

    return textures;
}

void Model::Draw(const unsigned int programId, const float4x4& view, const float4x4& proj, const float4x4& model)
{
	for (unsigned int i = 0; i < Meshes.size(); i++)
	{
        Meshes[i].Draw(programId, view, proj, model);
	}
}

float3 Model::GetModelSizeFactor() const
{
    ENGINE_LOG("OBB.DeltaX: %f", OBB.DeltaX());
    ENGINE_LOG("OBB.DeltaY: %f", OBB.DeltaY());
    ENGINE_LOG("OBB.DeltaZ: %f", OBB.DeltaZ());

    return float3(OBB.DeltaX(), OBB.DeltaY(), OBB.DeltaZ());
}

int Model::TextureFromFile(const char* path, const std::string& directory) const
{
    ILuint texid;

    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
    {
        ENGINE_LOG("[ERROR] Wrong DevIl version. Cannot load texture");
        return -1;
    }

    ilInit();
    ilGenImages(1, &texid);
    ilBindImage(texid);
    std::string textureRelativePath = std::string(path);
    std::string textureName = textureRelativePath.substr(textureRelativePath.find_last_of("/\\") + 1);

    std::vector<std::string> searchPaths;
    searchPaths.push_back(directory + "\\" + textureRelativePath);
    searchPaths.push_back(directory + "\\" + textureName);
    searchPaths.push_back(std::string(DefaultTexturePath) + "\\" + textureName);
    
    ILboolean success = IL_FALSE;

    for (int i = 0; i < searchPaths.size() && !success; ++i)
    {
        ENGINE_LOG("Try to load texture in: %s", searchPaths[i].c_str());
        success = ilLoadImage(searchPaths[i].c_str());
    }

    if (!success)
    {
        return -1;
    }

    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); 
    if (success != IL_TRUE)
    {
        return -1;
    }

    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_LOWER_LEFT)
    {
        iluFlipImage();
    }

    glActiveTexture(GL_TEXTURE0);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glGenerateMipmap(GL_TEXTURE_2D);

	// Texture specification 
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
        ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // We will use linear interpolation for magnification filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // We will use linear interpolation for minifying filter

    ilDeleteImages(1, &texid); // Because we have already copied image data into texture data we can release memory used by image
    return textureId;
}
