#include "UIComp.h"

#include "../ResourceManager/ResourceManager.h"
void UIComponent::CalculateMatrix()
{
    //Create a translate matrix
    AEMtx33 translateMtx;
    AEMtx33Trans(&translateMtx, pos.x, pos.y);

    //Create a rotation matrix
    AEMtx33 rotationMtx;
    AEMtx33Rot(&rotationMtx, rot);

    //Create a scale matrix
    AEMtx33 scaleMtx;
    AEMtx33Scale(&scaleMtx, scale.x, scale.y);

    //Concatenate them
    AEMtx33Concat(&transformMatrix, &rotationMtx, &scaleMtx);
    AEMtx33Concat(&transformMatrix, &translateMtx, &transformMatrix);
}

UIComponent::UIComponent(GameObject* _owner) : GraphicComponent(_owner), color(), tex(nullptr), mesh(nullptr), textureName(), Alpha(1.0f), rot(0.0f), transformMatrix()
{
    pos.x = 0;
    pos.y = 0;

    scale.x = 1;
    scale.y = 1;
    isDirty = false;
    isScreenSpace = false;
    CalculateMatrix();
    SetMesh();
}

UIComponent::~UIComponent()
{
    ResourceManager::GetInstance().UnloadResource(textureName);
    AEGfxMeshFree(mesh);
}

void UIComponent::Update()
{
    if (!mesh)
        return;

    // Get camera position
    float camX, camY;
    AEGfxGetCamPosition(&camX, &camY);

    // 매트릭스가 변경된 경우에만 재계산
    if (isDirty)
    {
        CalculateMatrix();
        isDirty = false;
    }

    // Set render mode for UI
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    // Set color to multiply
    AEGfxSetColorToMultiply(1, 1, 1, 1);

    // Set blend Mode
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    // Set transparency
    AEGfxSetTransparency(Alpha);

    // Set color to add
    AEGfxSetColorToAdd(color.r / 255.f, color.g / 255.f, color.b / 255.f, 0.f);

    // Create transformation matrix for UI (screen space)
    AEMtx33 uiTransform = transformMatrix;

    // Apply camera translation (screen position with camera)
    if (!isScreenSpace)
    {
        uiTransform.m[0][2] += camX;
        uiTransform.m[1][2] += camY;
    }

    // Set transform matrix
    AEGfxSetTransform(uiTransform.m);

    // Set texture
    AEGfxTextureSet(tex, 0, 0);

    // Draw the UI element
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void UIComponent::SetMesh()
{
    // Create quad for UI (similar to SpriteComp, but screen-locked)
    AEGfxMeshStart();

    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

    mesh = AEGfxMeshEnd();
}

void UIComponent::SetColor(const unsigned char& r, const unsigned char& g, const unsigned char& b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void UIComponent::SetTexture(std::string name)
{
    if (textureName != name)
        ResourceManager::GetInstance().UnloadResource(textureName);

    textureName = name;
    tex = ResourceManager::GetInstance().GetResource<AEGfxTexture>(name);
}

void UIComponent::SetAlpha(float alpha)
{
    Alpha = alpha;
}

void UIComponent::SetScreenSpace(bool a)
{
    isScreenSpace = a;
}

float UIComponent::GetAlpha() const
{
    return Alpha;
}

AEVec2 UIComponent::GetPos() const
{
    return pos;
}

AEVec2 UIComponent::GetScale() const
{
    return scale;
}

void UIComponent::SetPos(const AEVec2& position)
{
    pos = position;
    isDirty = true;  
}

void UIComponent::SetScale(const AEVec2& size)
{
    scale = size;
    isDirty = true; 
}

void UIComponent::SetRot(float angle)
{
    rot = angle;
    isDirty = true;  
}



void UIComponent::LoadFromJson(const json& data)
{
    auto compData = data.find("compData");

    if (compData != data.end())
    {
        // Load position
        auto p = compData->find("position");
        if (p != compData->end())
        {
            pos.x = (*p)["x"];
            pos.y = (*p)["y"];
        }

        // Load scale
        auto s = compData->find("scale");
        if (s != compData->end())
        {
            scale.x = (*s)["x"];
            scale.y = (*s)["y"];
        }

        // Load rotation
        auto r = compData->find("rotation");
        if (r != compData->end())
        {
            rot = *r;
        }

        // Load alpha
        auto a = compData->find("alpha");
        if (a != compData->end())
        {
            Alpha = *a;
        }

        // Load isScreenSpace flag
        auto ss = compData->find("isScreenSpace");
        if (ss != compData->end())
        {
            isScreenSpace = *ss;
        }

        // Load color
        auto c = compData->find("color");
        if (c != compData->end())
        {
            color.r = (*c)[0];
            color.g = (*c)[1];
            color.b = (*c)[2];
        }

        // Load texture name
        auto t = compData->find("textureName");
        if (t != compData->end())
        {
            textureName = *t;
            SetTexture(textureName);
        }

        // Recalculate matrix after loading
        CalculateMatrix();
        isDirty = true;
    }
}


json UIComponent::SaveToJson()
{
    json data;
    data["type"] = TypeName;

    json compData;

    // Position
    compData["position"] = { {"x", pos.x}, {"y", pos.y} };

    // Scale
    compData["scale"] = { {"x", scale.x}, {"y", scale.y} };

    // Rotation
    compData["rotation"] = rot;

    // Alpha
    compData["alpha"] = Alpha;

    // Screen Space flag
    compData["isScreenSpace"] = isScreenSpace;

    // Color
    compData["color"] = { color.r, color.g, color.b };

    // Texture name
    compData["textureName"] = textureName;

    data["compData"] = compData;

    return data;
}


BaseRTTI* UIComponent::CreateUIComponent(GameObject* owner)
{
    BaseRTTI* p = new UIComponent(owner);
    owner->AddComponent<UIComponent>(static_cast<UIComponent*>(p));
    return p;
}
