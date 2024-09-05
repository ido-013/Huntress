#include "StoreUI.h"
#include "../data/data.h"
#include "../Components/UIComp.h"
#include "../Components/PlayerComp.h"
#include "../Combat/Combat.h"
#include <random>

void StoreUI::SetUIVisibility(bool isVisible)
{
    int alphaValue = isVisible ? 1 : 0;

    //UIComponent* OpenSprite = Openbtn->GetComponent<UIComponent>();
    UIComponent* storeSprite = StorePopup->GetComponent<UIComponent>();
    UIComponent* Frame1 = Frame[0]->GetComponent<UIComponent>();
    UIComponent* Frame2 = Frame[1]->GetComponent<UIComponent>();
    UIComponent* Frame3 = Frame[2]->GetComponent<UIComponent>();
    UIComponent* Frame4 = Frame[3]->GetComponent<UIComponent>();
    UIComponent* Frame5 = Frame[4]->GetComponent<UIComponent>();
    UIComponent* Frame6 = Frame[5]->GetComponent<UIComponent>();
    UIComponent* CloseSprite = Closebtn->GetComponent<UIComponent>();
    UIComponent* HpSprite = UpHp->GetComponent<UIComponent>();
    UIComponent* AttackSprite = UpAttack->GetComponent<UIComponent>();
    UIComponent* DefenseSprite = UpDefense->GetComponent<UIComponent>();
    UIComponent* fullSprite = fullPotion->GetComponent<UIComponent>();
    UIComponent* smallSprite = smallPotion->GetComponent<UIComponent>();
    UIComponent* ArrowSprite = Arrow->GetComponent<UIComponent>();

    //OpenSprite->SetAlpha(isVisible ? 0 : 1);  // Open 버튼
    storeSprite->SetAlpha(alphaValue);        // 상점 팝업
    Frame1->SetAlpha(alphaValue);
    Frame2->SetAlpha(alphaValue);
    Frame3->SetAlpha(alphaValue);
    Frame4->SetAlpha(alphaValue);
    Frame5->SetAlpha(alphaValue);
    Frame6->SetAlpha(alphaValue);
    CloseSprite->SetAlpha(alphaValue);        // Close 버튼
    smallSprite->SetAlpha(alphaValue);        // 상품들
    DefenseSprite->SetAlpha(alphaValue);
    fullSprite->SetAlpha(alphaValue);
    HpSprite->SetAlpha(alphaValue);
    AttackSprite->SetAlpha(alphaValue);
    ArrowSprite->SetAlpha(alphaValue);
}

void StoreUI::SetStoreUI()
{
    isStore = true;
    SetUIVisibility(true);
}

void StoreUI::Setoff()
{
    isStore = false;
    SetUIVisibility(false);

}


void StoreUI::InitStoreUI(GameObject* player)
{
    CombatComp::isCombat = false;
    CombatComp::state = CombatComp::STATE::STORE;
    //// Open 버튼 설정
    //Openbtn = new GameObject();
    //Openbtn->AddComponent<UIComponent>();
    //UIComponent* OpenUI = Openbtn->GetComponent<UIComponent>();
    //OpenUI->SetScale({ 50,50 });
    //OpenUI->SetPos({ 0, 320 });
    //OpenUI->SetTexture("Assets/arrow.png");
    //OpenUI->SetColor(250, 0, 255);
    //OpenUI->SetAlpha(1);
    //Openbtn->AddComponent<ButtonComp>();
    //ButtonComp* OpenButton = Openbtn->GetComponent<ButtonComp>();
    //OpenButton->SetOnClickFunction([this]() {
    //    SetStoreUI();  // 상점 열기
    //    });
    //ButtonManager::GetInstance().RegisterButton(OpenButton);

    // Store Popup 설정
    StorePopup = new GameObject();
    StorePopup->AddComponent<UIComponent>();
    UIComponent* storeUI = StorePopup->GetComponent<UIComponent>();
    storeUI->SetScale({ 1200,600 });
    storeUI->SetPos({ 0, 0 });
    storeUI->SetTexture("Assets/UI/Storebg.png");
    storeUI->SetColor(0, 0, 0);
    storeUI->SetAlpha(0);

    Closebtn = new GameObject();
    Closebtn->AddComponent<UIComponent>();
    UIComponent* CloseUI = Closebtn->GetComponent<UIComponent>();
    CloseUI->SetScale({ 50,50 });
    CloseUI->SetPos({ 550, 250 });
    CloseUI->SetTexture("Assets/UI/Arrow.png");
    CloseUI->SetColor(250, 0, 0);
    CloseUI->SetAlpha(0);
    Closebtn->AddComponent<ButtonComp>();
    ButtonComp* CloseButton = Closebtn->GetComponent<ButtonComp>();
    CloseButton->SetOnClickFunction([this]() {
        Setoff();  // 상점 닫기
        CombatComp::ResetCombat();
        });
    ButtonManager::GetInstance().RegisterButton(CloseButton);
    Frame[0] = new GameObject();
    Frame[0]->AddComponent<UIComponent>();
    UIComponent* Frame1 = Frame[0]->GetComponent<UIComponent>();
    Frame1->SetScale({ 170,170 });
    Frame1->SetPos({ 400, 100 });
    Frame1->SetTexture("Assets/UI/itemFrame.png");
    Frame1->SetColor(0, 0, 0);
    Frame1->SetAlpha(0);
    Frame[1] = new GameObject();
    Frame[1]->AddComponent<UIComponent>();
    UIComponent* Frame2 = Frame[1]->GetComponent<UIComponent>();
    Frame2->SetScale({ 170,170 });
    Frame2->SetPos({ 200, 100 });
    Frame2->SetTexture("Assets/UI/itemFrame.png");
    Frame2->SetColor(0, 0, 0);
    Frame2->SetAlpha(0);
    Frame[2] = new GameObject();
    Frame[2]->AddComponent<UIComponent>();
    UIComponent* Frame3 = Frame[2]->GetComponent<UIComponent>();
    Frame3->SetScale({ 170,170 });
    Frame3->SetPos({ 0, 100 });
    Frame3->SetTexture("Assets/UI/itemFrame.png");
    Frame3->SetColor(0, 0, 0);
    Frame3->SetAlpha(0);
    Frame[3] = new GameObject();
    Frame[3]->AddComponent<UIComponent>();
    UIComponent* Frame4 = Frame[3]->GetComponent<UIComponent>();
    Frame4->SetScale({ 170,170 });
    Frame4->SetPos({ 400, -100 });
    Frame4->SetTexture("Assets/UI/itemFrame.png");
    Frame4->SetColor(0, 0, 0);
    Frame4->SetAlpha(0);
    Frame[4] = new GameObject();
    Frame[4]->AddComponent<UIComponent>();
    UIComponent* Frame5 = Frame[4]->GetComponent<UIComponent>();
    Frame5->SetScale({ 170,170 });
    Frame5->SetPos({ 200, -100 });
    Frame5->SetTexture("Assets/UI/itemFrame.png");
    Frame5->SetColor(0, 0, 0);
    Frame5->SetAlpha(0);
    Frame[5] = new GameObject();
    Frame[5]->AddComponent<UIComponent>();
    UIComponent* Frame6 = Frame[5]->GetComponent<UIComponent>();
    Frame6->SetScale({ 170,170 });
    Frame6->SetPos({ 0, -100 });
    Frame6->SetTexture("Assets/UI/itemFrame.png");
    Frame6->SetColor(0, 0, 0);
    Frame6->SetAlpha(0);
    // Article 1 설정
    Arrow = new GameObject();
    Arrow->AddComponent<UIComponent>();
    UIComponent* ArrowUI = Arrow->GetComponent<UIComponent>();
    ArrowUI->SetScale({ 120,120 });
    ArrowUI->SetPos({ 400, 100 });
    ArrowUI->SetTexture("Assets/UI/nomalize.png");
    ArrowUI->SetColor(0, 0, 0);
    ArrowUI->SetAlpha(0);
    Arrow->AddComponent<ButtonComp>();
    ButtonComp* art1Button = Arrow->GetComponent<ButtonComp>();
    art1Button->SetOnClickFunction([player]() {
        // Arrow 클릭 이벤트
        });
    ButtonManager::GetInstance().RegisterButton(art1Button);



    // FullPotion 설정
    fullPotion = new GameObject();
    fullPotion->AddComponent<UIComponent>();
    UIComponent* fullPotionUI = fullPotion->GetComponent<UIComponent>();
    fullPotionUI->SetScale({ 100,100 });
    fullPotionUI->SetPos({ 200, 100 });
    fullPotionUI->SetTexture("Assets/UI/fullpotion.png");
    fullPotionUI->SetColor(0, 0, 0);
    fullPotionUI->SetAlpha(0);
    fullPotion->AddComponent<ButtonComp>();
    ButtonComp* fullPotionButton = fullPotion->GetComponent<ButtonComp>();
    fullPotionButton->SetOnClickFunction([player]() {
        player->GetComponent<PlayerComp>()->playerData->hp = player->GetComponent<PlayerComp>()->playerData->maxLife;
        });
    ButtonManager::GetInstance().RegisterButton(fullPotionButton);

    // SmallPotion 설정
    smallPotion = new GameObject();
    smallPotion->AddComponent<UIComponent>();
    UIComponent* smallPotionUI = smallPotion->GetComponent<UIComponent>();
    smallPotionUI->SetScale({ 120,120 });
    smallPotionUI->SetPos({ 0, 100 });
    smallPotionUI->SetTexture("Assets/UI/smallpotion.png");
    smallPotionUI->SetColor(0, 0, 0);
    smallPotionUI->SetAlpha(0);
    smallPotion->AddComponent<ButtonComp>();
    ButtonComp* smallPotionButton = smallPotion->GetComponent<ButtonComp>();
    smallPotionButton->SetOnClickFunction([player]() {
        if (player->GetComponent<PlayerComp>()->playerData->hp + player->GetComponent<PlayerComp>()->playerData->maxLife * 0.1 < player->GetComponent<PlayerComp>()->playerData->maxLife)
            player->GetComponent<PlayerComp>()->playerData->hp += player->GetComponent<PlayerComp>()->playerData->maxLife * 0.1;
        else
            player->GetComponent<PlayerComp>()->playerData->hp = player->GetComponent<PlayerComp>()->playerData->maxLife;
        });
    ButtonManager::GetInstance().RegisterButton(smallPotionButton);

    // UpHp 설정
    UpHp = new GameObject();
    UpHp->AddComponent<UIComponent>();
    UIComponent* UpHpUI = UpHp->GetComponent<UIComponent>();
    UpHpUI->SetScale({ 120,120 });
    UpHpUI->SetPos({ 0, -100 });
    UpHpUI->SetTexture("Assets/UI/HearthUp.png");
    UpHpUI->SetColor(0, 0, 0);
    UpHpUI->SetAlpha(0);
    UpHp->AddComponent<ButtonComp>();
    ButtonComp* UpHpButton = UpHp->GetComponent<ButtonComp>();
    UpHpButton->SetOnClickFunction([player]() {
        player->GetComponent<PlayerComp>()->playerData->maxLife++;
        player->GetComponent<PlayerComp>()->playerData->hp++;
        });
    ButtonManager::GetInstance().RegisterButton(UpHpButton);

    // UpDefense 설정
    UpDefense = new GameObject();
    UpDefense->AddComponent<UIComponent>();
    UIComponent* UpDefenseUI = UpDefense->GetComponent<UIComponent>();
    UpDefenseUI->SetScale({ 120,120 });
    UpDefenseUI->SetPos({ 400, -100 });
    UpDefenseUI->SetTexture("Assets/UI/DefenseUp.png");
    UpDefenseUI->SetColor(0, 0, 0);
    UpDefenseUI->SetAlpha(0);
    UpDefense->AddComponent<ButtonComp>();
    ButtonComp* UpDefenseButton = UpDefense->GetComponent<ButtonComp>();
    UpDefenseButton->SetOnClickFunction([player]() {
        player->GetComponent<PlayerComp>()->playerData->armor++;
        });
    ButtonManager::GetInstance().RegisterButton(UpDefenseButton);

    // UpAttack 설정
    UpAttack = new GameObject();
    UpAttack->AddComponent<UIComponent>();
    UIComponent* UpAttackUI = UpAttack->GetComponent<UIComponent>();
    UpAttackUI->SetScale({ 120,120 });
    UpAttackUI->SetPos({ 200, -100 });
    UpAttackUI->SetTexture("Assets/UI/AttackUp.png");
    UpAttackUI->SetColor(0, 0, 0);
    UpAttackUI->SetAlpha(0);
    UpAttack->AddComponent<ButtonComp>();
    ButtonComp* UpAttackButton = UpAttack->GetComponent<ButtonComp>();
    UpAttackButton->SetOnClickFunction([player]() {
        player->GetComponent<PlayerComp>()->playerData->damage++;
        });
    ButtonManager::GetInstance().RegisterButton(UpAttackButton);
    SetStoreUI();
}

void StoreUI::UpdateStoreUI()
{

}

void ExitStoreUI()
{
    // 필요한 리소스 정리
}