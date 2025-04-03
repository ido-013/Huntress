#pragma once
#include <string>
#include "AEEngine.h"
#include "../ComponentManager/InterfaceComponent.h"

class UIComponent : public InterfaceComponent
{
private:
    void SetMesh();
    AEGfxTexture* tex = nullptr;    
    AEGfxVertexList* mesh = nullptr;        
    std::string textureName;   
    float Alpha;              
    float rot;
    AEVec2 pos;                
    AEVec2 scale;             
    AEMtx33 transformMatrix;
    struct Color {
        unsigned char r, g, b;
    } color;
    bool isDirty;
    bool isScreenSpace;
public:
    // 생성자 및 소멸자
    UIComponent(GameObject* _owner);
    virtual ~UIComponent();

    void Update() override;
    void SetPos(const AEVec2& position);
    void SetScale(const AEVec2& size);
    void SetRot(float angle);
    void SetColor(const unsigned char& r, const unsigned char& g, const unsigned char& b);
    void SetTexture(std::string name);
    void SetAlpha(float alpha);
    void SetScreenSpace(bool a);
	float GetAlpha() const;
    AEVec2 GetPos() const;
    AEVec2 GetScale() const;


    void CalculateMatrix();
 
    void LoadFromJson(const json& data) override;
    json SaveToJson() override;
    static BaseRTTI* CreateUIComponent(GameObject* owner);
    static constexpr const char* TypeName = "UIComponent";
};

