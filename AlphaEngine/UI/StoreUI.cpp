#include "StoreUI.h"
#include "../Data/Data.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include <random>


void StoreUI::SetUIVisibility(bool isVisible)
{
    int alphaValue = isVisible ? 1 : 0;

    SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
    SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
    SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
    SpriteComp* HpSprite = UpHp->GetComponent<SpriteComp>();
    SpriteComp* AttackSprite = UpAttack->GetComponent<SpriteComp>();
    SpriteComp* DefenseSprite = UpDefense->GetComponent<SpriteComp>();
    SpriteComp* fullSprite = fullPotion->GetComponent<SpriteComp>();
    SpriteComp* smallSprite = smallPotion->GetComponent<SpriteComp>();
    SpriteComp* ArrowSprite = Arrow->GetComponent<SpriteComp>();

    OpenSprite->SetAlpha(isVisible ? 0 : 1);  // Open 버튼
    storeSprite->SetAlpha(alphaValue);        // 상점 팝업
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
    // Open 버튼 설정
    Openbtn = new GameObject();
    Openbtn->AddComponent<SpriteComp>();
    Openbtn->AddComponent<TransformComp>();
    TransformComp* transOpen = Openbtn->GetComponent<TransformComp>();
    transOpen->SetScale({ 50,50 });
    transOpen->SetPos({ 0, 320 });
    SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
    OpenSprite->SetTexture("Assets/arrow.png");
    OpenSprite->SetColor(250, 0, 255);
    OpenSprite->SetAlpha(1);
    Openbtn->AddComponent<ButtonComp>();
    ButtonComp* OpenButton = Openbtn->GetComponent<ButtonComp>();
    OpenButton->SetOnClickFunction([this]() {
        SetStoreUI();  // 상점 열기
        });
    ButtonManager::GetInstance().RegisterButton(OpenButton);

    // Store Popup 설정
    StorePopup = new GameObject();
    StorePopup->AddComponent<SpriteComp>();
    StorePopup->AddComponent<TransformComp>();
    TransformComp* transStore = StorePopup->GetComponent<TransformComp>();
    transStore->SetScale({ 1200,600 });
    transStore->SetPos({ 0, 0 });
    SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
    storeSprite->SetTexture("Assets/arrow.png");
    storeSprite->SetColor(255, 255, 255);
    storeSprite->SetAlpha(0);

    // Close 버튼 설정
    Closebtn = new GameObject();
    Closebtn->AddComponent<SpriteComp>();
    Closebtn->AddComponent<TransformComp>();
    TransformComp* transClose = Closebtn->GetComponent<TransformComp>();
    transClose->SetScale({ 50,50 });
    transClose->SetPos({ 550, 250 });
    SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
    CloseSprite->SetTexture("Assets/arrow.png");
    CloseSprite->SetColor(250, 0, 0);
    CloseSprite->SetAlpha(0);
    Closebtn->AddComponent<ButtonComp>();
    ButtonComp* CloseButton = Closebtn->GetComponent<ButtonComp>();
    CloseButton->SetOnClickFunction([this]() {
        Setoff();  // 상점 닫기
        });
    ButtonManager::GetInstance().RegisterButton(CloseButton);

    // Article 1 설정
    Arrow = new GameObject();
    Arrow->AddComponent<SpriteComp>();
    Arrow->AddComponent<TransformComp>();
    TransformComp* transArt1 = Arrow->GetComponent<TransformComp>();
    transArt1->SetScale({ 150,150 });
    transArt1->SetPos({ 400, 100 });
    SpriteComp* art1Sprite = Arrow->GetComponent<SpriteComp>();
    art1Sprite->SetTexture("Assets/arrow.png");
    art1Sprite->SetColor(250, 250, 0);
    art1Sprite->SetAlpha(0);
    Arrow->AddComponent<ButtonComp>();
    ButtonComp* art1Button = Arrow->GetComponent<ButtonComp>();
    art1Button->SetOnClickFunction([player]() {  // 여기서 player를 캡처
        // Arrow 클릭 이벤트
        });
    ButtonManager::GetInstance().RegisterButton(art1Button);

    fullPotion = new GameObject();
    fullPotion->AddComponent<SpriteComp>();
    fullPotion->AddComponent<TransformComp>();
    TransformComp* transArt3 = fullPotion->GetComponent<TransformComp>();
    transArt3->SetScale({ 150,150 });
    transArt3->SetPos({ 200, 100 });
    SpriteComp* art3Sprite = fullPotion->GetComponent<SpriteComp>();
    art3Sprite->SetTexture("Assets/arrow.png");
    art3Sprite->SetColor(250, 250, 0);
    art3Sprite->SetAlpha(0);
    fullPotion->AddComponent<ButtonComp>();
    ButtonComp* art3Button = fullPotion->GetComponent<ButtonComp>();
    art3Button->SetOnClickFunction([player]() {  // player를 캡처
        player->GetComponent<PlayerComp>()->data.hp = player->GetComponent<PlayerComp>()->data.maxLife;
        });
    ButtonManager::GetInstance().RegisterButton(art3Button);

    smallPotion = new GameObject();
    smallPotion->AddComponent<SpriteComp>();
    smallPotion->AddComponent<TransformComp>();
    TransformComp* transArt6 = smallPotion->GetComponent<TransformComp>();
    transArt6->SetScale({ 150,150 });
    transArt6->SetPos({ 0, 100 });
    SpriteComp* art6Sprite = smallPotion->GetComponent<SpriteComp>();
    art6Sprite->SetTexture("Assets/arrow.png");
    art6Sprite->SetColor(250, 250, 0);
    art6Sprite->SetAlpha(0);
    smallPotion->AddComponent<ButtonComp>();
    ButtonComp* art6Button = smallPotion->GetComponent<ButtonComp>();
    art6Button->SetOnClickFunction([player]() {  // player를 캡처
        if (player->GetComponent<PlayerComp>()->data.hp + player->GetComponent<PlayerComp>()->data.maxLife * 0.1 < player->GetComponent<PlayerComp>()->data.maxLife)
            player->GetComponent<PlayerComp>()->data.hp += player->GetComponent<PlayerComp>()->data.maxLife * 0.1;
        else
            player->GetComponent<PlayerComp>()->data.hp = player->GetComponent<PlayerComp>()->data.maxLife;
        });
    ButtonManager::GetInstance().RegisterButton(art6Button);

    UpHp = new GameObject();
    UpHp->AddComponent<SpriteComp>();
    UpHp->AddComponent<TransformComp>();
    TransformComp* transArt5 = UpHp->GetComponent<TransformComp>();
    transArt5->SetScale({ 150,150 });
    transArt5->SetPos({ 0, -100 });
    SpriteComp* art5Sprite = UpHp->GetComponent<SpriteComp>();
    art5Sprite->SetTexture("Assets/arrow.png");
    art5Sprite->SetColor(250, 250, 0);
    art5Sprite->SetAlpha(0);
    UpHp->AddComponent<ButtonComp>();
    ButtonComp* art5Button = UpHp->GetComponent<ButtonComp>();
    art5Button->SetOnClickFunction([player]() {  // player를 캡처
        player->GetComponent<PlayerComp>()->data.maxLife++;
        });
    ButtonManager::GetInstance().RegisterButton(art5Button);

    UpDefense = new GameObject();
    UpDefense->AddComponent<SpriteComp>();
    UpDefense->AddComponent<TransformComp>();
    TransformComp* transArt2 = UpDefense->GetComponent<TransformComp>();
    transArt2->SetScale({ 150,150 });
    transArt2->SetPos({ 400, -100 });
    SpriteComp* art2Sprite = UpDefense->GetComponent<SpriteComp>();
    art2Sprite->SetTexture("Assets/arrow.png");
    art2Sprite->SetColor(250, 250, 0);
    art2Sprite->SetAlpha(0);
    UpDefense->AddComponent<ButtonComp>();
    ButtonComp* art2Button = UpDefense->GetComponent<ButtonComp>();
    art2Button->SetOnClickFunction([player]() {  // player를 캡처
        player->GetComponent<PlayerComp>()->data.armor++;
        });
    ButtonManager::GetInstance().RegisterButton(art2Button);

    UpAttack = new GameObject();
    UpAttack->AddComponent<SpriteComp>();
    UpAttack->AddComponent<TransformComp>();
    TransformComp* transArt4 = UpAttack->GetComponent<TransformComp>();
    transArt4->SetScale({ 150,150 });
    transArt4->SetPos({ 200, -100 });
    SpriteComp* art4Sprite = UpAttack->GetComponent<SpriteComp>();
    art4Sprite->SetTexture("Assets/arrow.png");
    art4Sprite->SetColor(250, 250, 0);
    art4Sprite->SetAlpha(0);
    UpAttack->AddComponent<ButtonComp>();
    ButtonComp* art4Button = UpAttack->GetComponent<ButtonComp>();
    art4Button->SetOnClickFunction([player]() {  // player를 캡처
        player->GetComponent<PlayerComp>()->data.damage++;
        });
    ButtonManager::GetInstance().RegisterButton(art4Button);
}


void StoreUI::UpdateStoreUI()
{
    if (!isStore) {
        Setoff();
    } else {
        SetStoreUI();
    }
}

void ExitStoreUI()
{
    // 필요한 리소스 정리
}
