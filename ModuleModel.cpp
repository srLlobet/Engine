#include "ModuleModel.h"
#include "Globals.h"
#include "Mesh.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
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
	Load("BakerHouse.gltf");
	return true;
}

void ModuleModel::Load(const char* assetFileName)
{
	App->GetRenderExercise()->ClearMeshes();

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
	//super quick work-around for delivery 
	for (const auto& node : model.nodes)
	{
		
		scalex = node.scale.empty() ? 0.05f : node.scale[0];
		scaley = node.scale.empty() ? 0.05f : node.scale[1];
		scalez = node.scale.empty() ? 0.05f : node.scale[2];

	}
	App->GetRenderExercise()->AdjustModelMatrix(scalex, scaley, scalez);

	for (const auto& srcMesh : model.meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh* mesh = new Mesh;

			mesh->Load(model, srcMesh, primitive);

			App->GetRenderExercise()->AddMesh(mesh);

		}
	}
	

}

void ModuleModel::LoadFromDragAndDrop(const char* assetFileName) {
	Load(assetFileName);
}
