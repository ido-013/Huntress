#pragma once
#include "../UIM/BtnManager.h"
#include <string>
#include <vector>
#include <functional>
//
//class ButtonComp;
//class PlayerComp;
class GameObject;
class ItemInfo;

class StoreUI {
    struct StoreItem {
        GameObject* itemObj = nullptr;
        ItemInfo* info = nullptr;
        std::function<void()> onClick;

    };
    std::vector<StoreItem> storeItems;
    std::vector<GameObject*> itemFrames;
    GameObject* storePopup = nullptr;
    GameObject* closeBtn = nullptr;
 

    bool isStoreOpen = false;
    bool isEsc = false;

    void CreateStoreItem(const std::string& name, const std::string& texturePath, const std::string& InfoPath, const AEVec2& pos, int cost,
        std::function<void()> onClick,
        std::function<void(UIComponent *)> onHover,
        std::function<void(UIComponent *)> outHover 
    );
    void CreateFrame(const AEVec2& pos);

public:
    StoreUI();
    ~StoreUI();
    static std::string goldText;
    void StoreOnEsc();
    void StoreOffEsc();
    bool getOpen();
    bool getisEsc();
    void SetUIVisibility(bool isVisible);
    void OpenStore();
    void CloseStore();
    void UpdateStoreUI();
    void InitStoreUI(GameObject* player);
    void ExitStoreUI();
};
