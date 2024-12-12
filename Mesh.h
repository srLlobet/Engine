#pragma once

using GLuint = unsigned int;
using GLsizei = int;

namespace tinygltf {
    class Model;
    class Mesh;
    class Primitive;
}


class Mesh
{
public:
	void Load(const tinygltf::Model& model, const tinygltf::Mesh& srcMesh, const tinygltf::Primitive& primitive);
    void Render();
private:
    GLuint vao;          // Vertex Array Object
    GLuint vbo;          // Vertex Buffer Object
    GLuint ebo;          // Element Buffer Object
    int materialIndex;   // Material index from tinygltf
    GLsizei indexCount;  // Number of indices for rendering

};

