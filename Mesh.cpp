#include "Mesh.h"
#include "tiny_gltf.h"
#include "SDL.h"
#include <GL/glew.h>
#include "lib/MathGeoLib/Math/float3.h"
#include "Application.h"
#include "ModuleRenderExercise.h"



/*
void Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
	std::vector<Vertex> vertices;

	const auto& itPos = primitive.attributes.find("POSITION"); //holds iterator position pointing for the POSITION key
	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second]; //gives index of position accessor
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView]; //defines byte offset, stride and buffer
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]); //position data begins here
		
		const auto& itTexCoord = primitive.attributes.find("TEXCOORD_0"); //repeat for textures
		if (itTexCoord != primitive.attributes.end()) {
			const tinygltf::Accessor& texAcc = model.accessors[itTexCoord->second];
			const tinygltf::BufferView& texView = model.bufferViews[texAcc.bufferView];
			const tinygltf::Buffer& texBuffer = model.buffers[texView.buffer];
			const unsigned char* bufferTexCoord = &(texBuffer.data[texAcc.byteOffset + texView.byteOffset]);

			// Combine positions and texture coordinates - interleaved format

			for (size_t i = 0; i < posAcc.count; ++i) {
				Vertex vertex;
				memcpy(vertex.position, bufferPos, sizeof(float) * 3);   // Copy position
				memcpy(vertex.texCoord, bufferTexCoord, sizeof(float) * 2); // Copy texture coordinates
				vertices.push_back(vertex);

				bufferPos += posView.byteStride;
				bufferTexCoord += texView.byteStride;
			}
		}

		if (primitive.indices > 0) {

		}

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		vertexCount = vertices.size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
			bufferPos += posView.byteStride;
		}
		
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}
*/