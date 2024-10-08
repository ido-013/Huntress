#include "SpriteComp.h"
#include "TransformComp.h"
#include "../ResourceManager/ResourceManager.h"

SpriteComp::SpriteComp(GameObject* _owner) : GraphicComponent(_owner), color(), tex(nullptr), mesh(nullptr), textureName(), Alpha(1)
{
	SetMesh();
}

SpriteComp::~SpriteComp()
{
	ResourceManager::GetInstance().UnloadResource(textureName);

	AEGfxMeshFree(mesh);
}

void SpriteComp::Update()
{
	if (!mesh)
		return;

	//Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	//Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	//Set blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	//Set transparency
	AEGfxSetTransparency(Alpha);

	//Set color to add
	AEGfxSetColorToAdd(color.r / 255.f, color.g / 255.f, color.b / 255.f, 0.f);

	//Set transform
	//Get the transform from my owner transfrom comp
	AEMtx33 transf = owner->GetComponent<TransformComp>()->GetMatrix();
	AEGfxSetTransform(transf.m);

	//Set texture
	AEGfxTextureSet(tex, 0, 0);

	//call DrawMesh
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void SpriteComp::SetMesh()
{
	//Create quad
	AEGfxMeshStart();

	if (owner->type == GameObject::LeftTri)
	{
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	}

	else if (owner->type == GameObject::RightTri)
	{
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	}

	else if (owner->type == GameObject::LeftTri_R)
	{
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	}

	else if (owner->type == GameObject::RightTri_R)
	{
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	}
		
	else
	{
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	}

	mesh = AEGfxMeshEnd();
}

void SpriteComp::SetColor(const unsigned char& r, const unsigned char& g, const unsigned char& b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

void SpriteComp::SetTexture(std::string name)
{
	if (textureName != name)
		ResourceManager::GetInstance().UnloadResource(textureName);
	
	textureName = name;
	tex = ResourceManager::GetInstance().GetResource<AEGfxTexture>(name);
}

void SpriteComp::SetAlpha(float alpha)
{
	Alpha = alpha;
}

float SpriteComp::GetAlpha()
{
	return Alpha;
}

void SpriteComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("color");
		color.r = it->begin().value();
		color.g = (it->begin() + 1).value();
		color.b = (it->begin() + 2).value();

		it = compData->find("textureName");
		textureName = it.value();
		SetTexture(textureName);

		it = compData->find("alpha");
		Alpha = it.value();
	}
}

json SpriteComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["color"] = { color.r, color.g, color.b };
	compData["textureName"] = textureName;
	compData["alpha"] = Alpha;
	data["compData"] = compData;

	return data;
}

BaseRTTI* SpriteComp::CreateSpriteComponent(GameObject* owner)
{
	BaseRTTI* p = new SpriteComp(owner);
	owner->AddComponent<SpriteComp>(static_cast<SpriteComp*>(p));
	return p;
}
