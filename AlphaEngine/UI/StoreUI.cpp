#include "StoreUI.h"
#include <iostream>
#include "../Components/UIComp.h"
#include "../Components/PlayerComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/AudioComp.h"
#include "../Components/SubtitleComp.h"
#include "../UI/ItemInfo.h"
#include <string>
#define SUBTITLE {f32(-0.5), f32(0.7)}
#define SUB_GOLD {f32(0.3), f32( 0.455)}
std::string StoreUI::goldText = "";
 #define PLAY_AUDIO_PURCHASE GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/coin-donation.mp3")
 #define PLAY_AUDIO_ERROR GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/error.mp3")
 //#define PLAY_AUDIO_HOVER GameObjectManager::GetInstance().GetObj("background")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/Push3.wav") 
 void StoreUI::CreateStoreItem(const std::string& name, const std::string& texturePath, const std::string& InfoPath, const AEVec2& pos, int cost,
     std::function<void()> onClick,
     std::function<void(UIComponent*)> onHover = nullptr,
     std::function<void(UIComponent*)> outHover = nullptr) {
     StoreItem item;
 
    item.itemObj = new GameObject();
    item.itemObj->AddComponent<UIComponent>();
    UIComponent* ui = item.itemObj->GetComponent<UIComponent>();
    ui->SetScale({ 120, 120 });
    ui->SetPos(pos);
    ui->SetTexture(texturePath);
    ui->SetAlpha(0);

    item.info = new ItemInfo();
    item.info->CreateItemInfo(name, InfoPath);
    item.itemObj->AddComponent<ButtonComp>();
    ButtonComp* button = item.itemObj->GetComponent<ButtonComp>();
    button->SetOnClickFunction(onClick);
    button->SetOnHoverFunction([ui,onHover, name, &item]() {
        ui->SetColor(120, 120, 120);
        ui->SetScale({ 130, 130 });

        if (onHover) {onHover(ui);}
        s32 mouseX, mouseY;
        AEInputGetCursorPosition(&mouseX, &mouseY);
        mouseY = -mouseY + 450;
        mouseX = mouseX - 800;
        AEVec2 mousePos = { static_cast<float>(mouseX)+125, static_cast<float>(mouseY)-125 };
        item.info->SetPosition(name, mousePos);
        item.info->SetonInfo(name);
        });
    button->SetOnHoverOutFunction([ui, outHover, name, &item]() {
        ui->SetColor(0, 0, 0);
        ui->SetScale({ 120, 120 });
        item.info->SetoffInfo(name);
        if (outHover) {outHover(ui);}
        });
    storeItems.push_back(item);
}


void StoreUI::CreateFrame(const AEVec2& pos) {
    GameObject* frame = new GameObject();
    frame->AddComponent<UIComponent>();
    UIComponent* frameUI = frame->GetComponent<UIComponent>();
    frameUI->SetScale({ 170, 170 });
    frameUI->SetPos(pos);
    frameUI->SetTexture("Assets/UI/itemFrame.png");
    frameUI->SetAlpha(0);

    itemFrames.push_back(frame);
}

StoreUI::StoreUI()
{
    std::cout << __FUNCTION__ << std::endl;
}

StoreUI::~StoreUI()
{
    for (auto& it : storeItems)
    {
        delete it.info;
    }
}

void StoreUI::StoreOnEsc()
{
    isEsc = true;
    CloseStore();
}

void StoreUI::StoreOffEsc()
{

    isEsc = false;
    OpenStore();
}
bool StoreUI::getOpen()
{
    return isStoreOpen;
}
bool StoreUI::getisEsc()
{
    return isEsc;
}
void StoreUI::SetUIVisibility(bool isVisible) {
    bool alphaValue = isVisible ? true : false;
    storePopup->GetComponent<UIComponent>()->SetAlpha(alphaValue);
    for (auto& frame : itemFrames) {
        frame->GetComponent<UIComponent>()->SetAlpha(alphaValue);
    }
    for (auto& item : storeItems) {
        item.itemObj->GetComponent<UIComponent>()->SetAlpha(alphaValue);
    }
    closeBtn->GetComponent<UIComponent>()->SetAlpha(alphaValue);
}

void StoreUI::OpenStore() {

    isStoreOpen = true;
    SetUIVisibility(true);
}

void StoreUI::CloseStore() {
    isStoreOpen = false;
    SetUIVisibility(false);
    SubtitleComp::RemoveSubtitle("goldText");
}

void StoreUI::InitStoreUI(GameObject* player) {
    CombatComp::isCombat = false;
    CombatComp::state = CombatComp::STATE::STORE;
    SubtitleComp::AddSubtitle({ SUB_GOLD, float(0.6), "goldText", f32(0.9), f32(0.9), f32(0), 1 });
    // Initialize Store Popup
    storePopup = new GameObject();
    storePopup->AddComponent<UIComponent>();
    UIComponent* popupUI = storePopup->GetComponent<UIComponent>();
    popupUI->SetScale({ 1200, 600 });
    popupUI->SetPos({ 0, 0 });
    popupUI->SetTexture("Assets/UI/Storebg.png");
    popupUI->SetAlpha(0);

    // Initialize Close Button
    closeBtn = new GameObject();
    closeBtn->AddComponent<UIComponent>();
    UIComponent* closeUI = closeBtn->GetComponent<UIComponent>();
    closeUI->SetScale({ 50, 50 });
    closeUI->SetPos({ 550, 250 });
    closeUI->SetTexture("Assets/UI/Arrow.png");
    closeUI->SetAlpha(0);
    closeBtn->AddComponent<ButtonComp>();
    ButtonComp* closeButton = closeBtn->GetComponent<ButtonComp>();
    closeButton->SetOnClickFunction([this]() {
        CloseStore();
        CombatComp::ResetCombat();
        });

    // Create frames for the store items
    CreateFrame({ 400, 100 });
    CreateFrame({ 200, 100 });
    CreateFrame({ 0, 100 });
    CreateFrame({ -400, 100 });
    CreateFrame({ -200, 100 });
    CreateFrame({ 400, -100 });
    CreateFrame({ 200, -100 });
    CreateFrame({ 0, -100 });
    CreateFrame({ -400, -100 });
    CreateFrame({ -200, -100 });
    // Store Items (Full Potion, Small Potion, Health, Attack, Defense)
    CreateStoreItem("Defense Upgrade", "Assets/UI/DefenseUp.png","Assets/UI/ArmorupInfo.png", {400, -100}, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 15) {
            playerComp->playerData->armor += 1;
            playerComp->playerData->gold -= 15;
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Defense Increased!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_PURCHASE;
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("Gods", "Assets/UI/nomalize.png", "Assets/UI/GodInfo.png", { 400, 100 }, 75, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->inventory.isGBY)
        {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "You Already Have This!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        else if (playerComp->playerData->gold >= 75) {
            playerComp->playerData->inventory.isGBY = true;
            playerComp->playerData->gold -= 75;
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Gods Bless You...", 0, 1, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_PURCHASE;
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        
        },
        //onHover [target space] (type) {function}
        [](UIComponent* ui) {
       

        },
        //out Hover
        [](UIComponent* ui) {
            
        }
    );
    CreateStoreItem("Attack Upgrade", "Assets/UI/AttackUp.png","Assets/UI/DamageupInfo.png", { 200, -100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 10) {
            playerComp->playerData->damage += 1;
            playerComp->playerData->gold -= 10;
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Attack Increased!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_PURCHASE;
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("Full Potion", "Assets/UI/fullpotion.png", "Assets/UI/LargepotionInfo.png", { 200, 100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 10) {
            if (playerComp->playerData->hp == playerComp->playerData->maxLife) {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Already Full...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
            else {
                playerComp->playerData->hp = (((playerComp->playerData->hp + playerComp->playerData->maxLife * 0.3) < (playerComp->playerData->maxLife)) ? float((playerComp->playerData->hp + playerComp->playerData->maxLife * 0.3)) : (playerComp->playerData->maxLife));
                playerComp->playerData->gold -= 10;
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Fully Healed!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_PURCHASE;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("Health Upgrade", "Assets/UI/HearthUp.png","Assets/UI/HealthupInfo.png", { 0, -100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 10) {
            playerComp->playerData->maxLife += 5;
            playerComp->playerData->hp += 5;
            playerComp->playerData->gold -= 10;
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Max HP Increased!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_PURCHASE;
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("smallpotion", "Assets/UI/smallpotion.png","Assets/UI/SmallpotionInfo.png", { 0, 100 }, 5, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 5) {
            if (playerComp->playerData->hp == playerComp->playerData->maxLife) {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Already Full...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
            else {
                playerComp->playerData->hp =(((playerComp->playerData->hp + playerComp->playerData->maxLife * 0.1) < (playerComp->playerData->maxLife)) ? float((playerComp->playerData->hp + playerComp->playerData->maxLife * 0.1)) : (playerComp->playerData->maxLife));
                playerComp->playerData->gold -= 5;
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Small Heal!", 0, 1, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_PURCHASE;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("Orbit", "Assets/UI/Orbit.png","Assets/UI/OrbitInfo.png", { -200, -100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 7) {
            if (playerComp->playerData->inventory.AddItem(Data::PlayerData::inventory.Orbit))
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[Data::PlayerData::inventory.Orbit + 5], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                playerComp->playerData->gold -= 7;
                PLAY_AUDIO_PURCHASE;
            }
            else
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[9], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
    });
   

   

    CreateStoreItem("Stun", "Assets/UI/stun.png","Assets/UI/StunarrowInfo.png", { -200, 100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 7) {
            if (playerComp->playerData->inventory.AddItem(Data::PlayerData::inventory.Stun))
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[Data::PlayerData::inventory.Stun + 5], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                playerComp->playerData->gold -= 7;
                PLAY_AUDIO_PURCHASE;
            }
            else
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[9], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
   
    CreateStoreItem("Straight", "Assets/UI/StraightArrow.png","Assets/UI/StraightarrowInfo.png", { -400, -100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 7) {
            if (playerComp->playerData->inventory.AddItem(Data::PlayerData::inventory.Straight))
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[Data::PlayerData::inventory.Straight + 5], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                playerComp->playerData->gold -= 7;
                PLAY_AUDIO_PURCHASE;
            }
            else
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[9], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
        });
    CreateStoreItem("Bigger", "Assets/UI/Bigger.png","Assets/UI/BiggerInfo.png", { -400, 100 }, 15, [player]() {
        PlayerComp* playerComp = player->GetComponent<PlayerComp>();
        if (playerComp->playerData->gold >= 7) {
            if (playerComp->playerData->inventory.AddItem(Data::PlayerData::inventory.Big))
            {
                playerComp->playerData->gold -= 7;
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[Data::PlayerData::inventory.Big + 5], 1, 0, 0, 1}, 2, 0.7, 0.7});
                PLAY_AUDIO_PURCHASE;
            }
            else
            {
                SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, subtitleOfItem[9], 1, 0, 0, 1}, 2, 0.7, 0.7 });
                PLAY_AUDIO_ERROR;
            }
        }
        else {
            SubtitleComp::IntersectDissolveText({ {SUBTITLE, 1, "Not Enough Gold...", 1, 0, 0, 1}, 2, 0.7, 0.7 });
            PLAY_AUDIO_ERROR;
        }
    });

    OpenStore();
}

void StoreUI::UpdateStoreUI() {
    if (SubtitleComp::FindSubtitle("goldText")) {
        goldText = "GOLD : " + std::to_string(GameObjectManager::GetInstance().GetObj("player")->GetComponent<PlayerComp>()->playerData->gold);
        SubtitleComp::ModifySubtitle("goldText", goldText);
    }
}

void StoreUI::ExitStoreUI() {
    SubtitleComp::ClearSubtitle();
}
