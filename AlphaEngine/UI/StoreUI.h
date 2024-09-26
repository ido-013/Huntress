#pragma once
#include "../UIM/BtnManager.h"
#include <string>
#include <vector>

class ButtonComp;
class PlayerComp;
class GameObject;

struct StoreItem {
    std::string name;
    std::string texturePath;
    int cost;
    GameObject* itemObj;
    std::function<void()> onClick;
};

class StoreUI {
    std::vector<StoreItem> storeItems;
    std::vector<GameObject*> itemFrames;
    GameObject* storePopup = nullptr;
    GameObject* closeBtn = nullptr;
    bool isStoreOpen = false;

    void CreateStoreItem(const std::string& name, const std::string& texturePath, const AEVec2& pos, int cost, std::function<void()> onClick);
    void CreateFrame(const AEVec2& pos);

public:
    static std::string goldText;

    void SetUIVisibility(bool isVisible);
    void OpenStore();
    void CloseStore();
    void InitStoreUI(GameObject* player);
    void UpdateStoreUI();
    void ExitStoreUI();
};
