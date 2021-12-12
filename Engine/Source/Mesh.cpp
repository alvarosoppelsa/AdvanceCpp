#include "Mesh.h"
#include "Globals.h"
#include "GL/glew.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    Vertices = vertices;
    Indices = indices;
    Textures = textures;

    SetupMesh();
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
        &Indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(const unsigned int programId, const float4x4& view, const float4x4& proj, const float4x4& model)
{
    glUseProgram(programId);
    glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_TRUE, (const float*)&model);
    glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_TRUE, (const float*)&view);
    glUniformMatrix4fv(glGetUniformLocation(programId, "proj"), 1, GL_TRUE, (const float*)&proj);

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = Textures[i].Type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }
        //shader.setFloat(("material." + name + number).c_str(), i);
        glUniform1i(glGetUniformLocation(programId, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].Id);
    }
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //glActiveTexture(GL_TEXTURE0);
    //for (unsigned int i = 0; i < Textures.size(); i++)
    //{
    //	// TODO: For more than one texture it's needed to change texture names. See example above
    //    glBindTexture(GL_TEXTURE_2D, Textures[i].Id);
    //}

    //glUniform1i(glGetUniformLocation(programId, "diffuse"), 0);
    // draw mesh
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);
    //glBindVertexArray(0);
}