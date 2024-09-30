#pragma once
#include "../UIM/BtnManager.h"
#include <string>
#include <vector>
#include <functional>

#define SUBTITLE {f32(-0.5), f32(0.7)}
#define SUB_GOLD {f32(0.3), f32( 0.465)}
#define SUB_DEF {f32(0.5),f32(- 0.46)}
#define SUB_ATK {f32(0.25),f32(- 0.46)}
#define SUB_HPU {f32(-0.02),f32(- 0.46)}
#define PLAY_AUDIO_PURCHASE GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/coin-donation.mp3")
#define PLAY_AUDIO_ERROR GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/error.mp3")
//#define PLAY_AUDIO_HOVER GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/Push3.wav") 


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
    static std::string atkText;
    static std::string defText;
    static std::string hpuText;
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
