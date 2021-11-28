#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"

struct Vertex
{
    float3 Position;
    float3 Normal;
    float2 TexCoords;
};

struct Texture
{
    unsigned int Id;
    std::string Type;
    std::string Path;
};

class Mesh
{
public:
    // mesh data
    std::vector<Vertex>       Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture>      Textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(const unsigned int programId, const float4x4& view, const float4x4& proj, const float4x4& model);

private:
    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void setupMesh();
};

