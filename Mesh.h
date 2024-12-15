#pragma once

#include <string>

using GLuint = unsigned int;
using GLsizei = int;
using GLfloat = float;

namespace tinygltf {
    class Model;
    class Mesh;
    class Primitive;
}

struct Vertex {
    float position[3];
    float texCoord[2];
};

//materia properties
struct Material {
    GLuint baseColorTextureID = 0;
    GLfloat baseColorFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Base color RGBA
    GLfloat metallicFactor = 0.0f;    // Metallic factor
    GLfloat roughnessFactor = 0.0f;   // Roughness factor
};

class Mesh
{
public:

    Mesh();
    virtual ~Mesh();

	void Load(const tinygltf::Model& model, const tinygltf::Mesh& srcMesh, const tinygltf::Primitive& primitive);
    void LoadMaterials(const tinygltf::Model& model, int materialIndex);

    static std::wstring StringToWString(const std::string& str);

    GLuint GetVBO() const { return vbo; }
    GLuint GetEBO() const { return ebo; }
    GLuint GetVAO() const { return vao; }
    int GetVertexCount() const { return vertexCount;  }
    GLsizei GetIndexCount() const { return indexCount; }
    const Material GetMaterial() const { return material; }



private:
    GLuint vao;          // Vertex Array Object
    GLuint vbo;          // Vertex Buffer Object
    GLuint ebo;          // Element Buffer Object
    int vertexCount;
    GLsizei materialIndex;   // Material index from tinygltf
    GLsizei indexCount;  // Number of indices for rendering
    Material material;
};

