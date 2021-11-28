#include "Model.h"
#include "Globals.h"

#include "GL/glew.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "Math/float3.h"

Model::Model(const char* file)
{
	Load(file);
}

/*
 * OTHER ASSIMP POSTPROCESS USEFULL OPTIONS ARE:
 * aiProcess_GenNormals
 * aiProcess_SplitLargeMeshes
 * aiProcess_OptimizeMeshes
*/
void Model::Load(const char* file)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		ENGINE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
		return;
	}
	std::string path = file;
	Directory = path.substr(0, path.find_last_of('/'));

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
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.Id = TextureFromFile(str.C_Str(), Directory);
            texture.Type = typeName;
            texture.Path = str.C_Str();
            textures.push_back(texture);
            TexturesLoaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

void Model::Draw(const unsigned int programId, const float4x4& view, const float4x4& proj, const float4x4& model)
{
	for (unsigned int i = 0; i < Meshes.size(); i++)
		Meshes[i].Draw(programId, view, proj, model);
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{

    ILuint texid;

    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
    {
        /* wrong DevIL version */
        return false;
    }
    ilInit();											/* Initialization of DevIL */
    ilGenImages(1, &texid);							    /* Generation of one image name */
    ilBindImage(texid);									/* Binding of image name */
    ILboolean success = ilLoadImage(path);	        /* Loading of image "image.jpg" */

    if (success != IL_TRUE)
    {
        return false;
    }
    /* Convert every color component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); 
    if (success != IL_TRUE)
    {
        return false;
    }

    // TODO: Flip texture if upside down
    //ILinfo ImageInfo;
    //iluGetImageInfo(&ImageInfo);
    //if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    //{
    //    iluFlipImage();
    //}

    //glActiveTexture(GL_TEXTURE0);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glGenerateMipmap(GL_TEXTURE_2D);

	// Texture specification 
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
        ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

    // Texture parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   /* We will use linear interpolation for magnification filter */
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   /* We will use linear interpolation for minifying filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data we can release memory used by image. */
}
