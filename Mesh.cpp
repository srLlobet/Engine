#include "Mesh.h"
#include "tiny_gltf.h"
#include "SDL.h"
#include <GL/glew.h>
#include "lib/MathGeoLib/Math/float3.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleOpenGL.h"




void Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
	std::vector<Vertex> vertices;
	const float defaultTexCoord[2] = { 0.0f, 0.0f };

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
		const unsigned char* bufferTexCoord = nullptr;
		size_t texStride = 0;

		if (itTexCoord != primitive.attributes.end()) {
			const tinygltf::Accessor& texAcc = model.accessors[itTexCoord->second];
			const tinygltf::BufferView& texView = model.bufferViews[texAcc.bufferView];
			const tinygltf::Buffer& texBuffer = model.buffers[texView.buffer];
			const unsigned char* bufferTexCoord = &(texBuffer.data[texAcc.byteOffset + texView.byteOffset]);
			texStride = texView.byteStride;
		}
		
		// Combine positions and texture coordinates - interleaved format
		// if no textures, fill with defaultTexCoord

		for (size_t i = 0; i < posAcc.count; ++i) {
			Vertex vertex;

			memcpy(vertex.position, bufferPos, sizeof(float) * 3);   // Copy position

			if (bufferTexCoord) {
				memcpy(vertex.texCoord, bufferTexCoord, sizeof(float) * 2); // Copy texture coordinates
				bufferTexCoord += texStride; // Increment texture buffer pointer
			}
			else {
				// If no texture coordinates,  default values
				memcpy(vertex.texCoord, defaultTexCoord, sizeof(float) * 2);
			}
			vertices.push_back(vertex);

			// check if bytestride is provided

			if (posView.byteStride == 0) {
				bufferPos += sizeof(float) * 3; 
			}
			else {
				bufferPos += posView.byteStride;
			}
			

		}
		

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		vertexCount = vertices.size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		if (primitive.indices >= 0) {

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			

			const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
			const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
			const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset + indView.byteOffset]);

				//INDICES
			std::vector<uint32_t> indices(indAcc.count);

			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT) {
				// No conversion needed, just copy the data directly
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indAcc.count * sizeof(uint32_t), buffer, GL_STATIC_DRAW);

			}
			else if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT) {
				// Convert from uint16_t to uint32_t
				const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
				for (size_t i = 0; i < indAcc.count; ++i) {
					indices[i] = static_cast<uint32_t>(bufferInd[i]);
				}
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
			}
			else if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE) {
				// Convert from uint8_t to uint32_t
				const uint8_t* bufferInd = reinterpret_cast<const uint8_t*>(buffer);
				for (size_t i = 0; i < indAcc.count; ++i) {
					indices[i] = static_cast<uint32_t>(bufferInd[i]);
				}
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
			}
			else {
				LOG("Unsupported index component type: ", indAcc.componentType);
			}


			indexCount = indAcc.count;
		}

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Set up the vertex attribute pointers
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // Position attribute
		glEnableVertexAttribArray(0);

		if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3)); // TexCoord attribute
			glEnableVertexAttribArray(1);
		}

		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		// Unbind VAO 
		glBindVertexArray(0);
	}

	int materialIndex = primitive.material; // Fetch material index from primitive
	LoadMaterials(model, materialIndex);    // Load material and assign textures
}


void Mesh::LoadMaterials(const tinygltf::Model &srcModel, int materialIndex)
{

	const tinygltf::Material& srcMaterial = srcModel.materials[materialIndex];

	if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
	{
		const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
		const tinygltf::Image& image = srcModel.images[texture.source];
		std::wstring uriW = StringToWString(image.uri);
		material.baseColorTextureID = App->GetOpenGL()->LoadTextureToGPU(uriW.c_str());
	}
	
	if (!srcMaterial.pbrMetallicRoughness.baseColorFactor.empty()) {
		for (int i = 0; i < 4; ++i) {
			material.baseColorFactor[i] = srcMaterial.pbrMetallicRoughness.baseColorFactor[i];
		}
	}

	
	// Metallic factor and roughness factor

	material.metallicFactor = srcMaterial.pbrMetallicRoughness.metallicFactor;
	//material.roughnessFactor = srcMaterial.pbrMetallicRoughness.roughnessFactor;


}

std::wstring Mesh::StringToWString(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}
