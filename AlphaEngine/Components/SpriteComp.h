#pragma once
#include <string>
#include "AEEngine.h"
#include "../ComponentManager/GraphicComponent.h"

class SpriteComp : public GraphicComponent
{
public:
	struct Color
	{
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
	};

private:
	//mesh of points (quad)
	// All my objects have the same quad,
	// so I will NOT make it a member variable

	//text coords (UV)

	//color
	Color color;

	//texture
	AEGfxTexture* tex = nullptr;
	AEGfxVertexList* mesh;

	//Render mode?
	//Blend mode?
	//Transparency?

	std::string textureName;

public:
	SpriteComp(GameObject* _owner);
	~SpriteComp();

	//Draw
	void Update() override;

	//Gettors/Settors
	Color& GetColor() { return color; }
	void SetColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);

	void SetTexture(std::string s);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateSpriteComponent(GameObject* owner);
	static constexpr const char* TypeName = "SpriteComp";
};
