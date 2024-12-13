#pragma once

using GLuint = unsigned int;
using GLsizei = int;

namespace tinygltf {
    class Model;
    class Mesh;
    class Primitive;
}

struct Vertex {
    float position[3];
    float texCoord[2];
};

class Mesh
{
public:

	//void Load(const tinygltf::Model& model, const tinygltf::Mesh& srcMesh, const tinygltf::Primitive& primitive);
    //void Render();

	//void Load(const tinygltf::Model& model, const tinygltf::Mesh& srcMesh, const tinygltf::Primitive& primitive);
    void Render();
    GLuint GetVBO() { return vbo; }
    GLsizei GetVertexCount() { return vertexCount;  }


private:
    GLuint vao;          // Vertex Array Object
    GLuint vbo;          // Vertex Buffer Object
    GLuint ebo;          // Element Buffer Object
    int vertexCount;
    GLsizei materialIndex;   // Material index from tinygltf
    GLsizei indexCount;  // Number of indices for rendering

};

