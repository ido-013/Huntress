#include "ItemInfo.h"
#include "../GameObject/GameObject.h"
#include "../Components/UIComp.h"
#include "../GameObjectManager/GameObjectManager.h"
ItemInfo::~ItemInfo()
{
}
void ItemInfo::CreateItemInfo(const std::string& name, const std::string& texturePath)
{
	GameObject* Infoitem = new GameObject(name);
	Infoitem->AddComponent<UIComponent>();
	UIComponent* InfoUI = Infoitem->GetComponent<UIComponent>();
	InfoUI->SetScale({300,350});
	InfoUI->SetPos({ 0,0 });
	InfoUI->SetTexture(texturePath);
	InfoUI->SetColor(0,0,0);
	InfoUI->SetAlpha(0);
}

void ItemInfo::SetonInfo(const std::string& name)
{
	GameObject* obj = GameObjectManager::GetInstance().GetObj(name);
	if (obj) { 
		UIComponent* uiComp = obj->GetComponent<UIComponent>();
		if (uiComp) {
			uiComp->SetAlpha(1);
		}
	}
}


void ItemInfo::SetoffInfo(const std::string& name)
{
	GameObject* obj = GameObjectManager::GetInstance().GetObj(name);
	if (obj) { // Check for null pointer
		UIComponent* uiComp = obj->GetComponent<UIComponent>();
		if (uiComp) {
			uiComp->SetAlpha(0);
		}
	}
}


void ItemInfo::SetPosition(const std::string& name, const AEVec2& newPosition)
{
	GameObject* obj = GameObjectManager::GetInstance().GetObj(name);
	if (obj) { // Check for null pointer
		UIComponent* uiComp = obj->GetComponent<UIComponent>();
		if (uiComp) {
			uiComp->SetPos(newPosition);
		}
	}
}



