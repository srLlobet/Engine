#include "ModuleModel.h"
#include "Globals.h"
#include "Mesh.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_IMPLEMENTATION //ONLY IN MODULEMODEL
#include "tiny_gltf.h" 


ModuleModel::ModuleModel()
{

}

ModuleModel::~ModuleModel()
{

}



bool ModuleModel::Init()
{
	Load("basicTriangle.gltf");
	return true;
}

void ModuleModel::Load(const char* assetFileName)
{

	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	std::string err, warn;

	bool ret = gltfContext.LoadASCIIFromFile(&model, &err, &warn, assetFileName);
	if (!ret)
	{
		if (!warn.empty()) {
			LOG("Warn: %s\n", warn.c_str());
		}

		if (!err.empty()) {
			LOG("Err: %s\n", err.c_str());
		}

		if (!ret) {
			LOG("Failed to parse glTF\n");
		}
	}

	for (const auto& srcMesh : model.meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh* mesh = new Mesh;
			//mesh->Load(model, srcMesh, primitive);
		}
	}

}
