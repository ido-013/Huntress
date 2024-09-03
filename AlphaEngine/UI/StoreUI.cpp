#include "StoreUI.h"
#include <random>

GameObject* Openbtn = nullptr;
GameObject* StorePopup = nullptr;
GameObject* Closebtn = nullptr;
GameObject* article_1 = nullptr;
GameObject* article_2 = nullptr;
GameObject* article_3 = nullptr;
GameObject* article_4 = nullptr;

bool isStore = false;

void SetStoreUI()
{
    isStore = true;
    SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
    SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
    SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
    SpriteComp* art1Sprite = article_1->GetComponent<SpriteComp>();
    SpriteComp* art2Sprite = article_2->GetComponent<SpriteComp>();
    SpriteComp* art3Sprite = article_3->GetComponent<SpriteComp>();
    SpriteComp* art4Sprite = article_4->GetComponent<SpriteComp>();

    OpenSprite->SetAlpha(0);  // Open 버튼은 숨김
    storeSprite->SetAlpha(1);  // 상점 팝업 표시
    CloseSprite->SetAlpha(1);  // Close 버튼 표시
    art1Sprite->SetAlpha(1);   // 상품들 표시
    art2Sprite->SetAlpha(1);
    art3Sprite->SetAlpha(1);
    art4Sprite->SetAlpha(1);
}

void Setoff()
{
    isStore = false;
    SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
    SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
    SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
    SpriteComp* art1Sprite = article_1->GetComponent<SpriteComp>();
    SpriteComp* art2Sprite = article_2->GetComponent<SpriteComp>();
    SpriteComp* art3Sprite = article_3->GetComponent<SpriteComp>();
    SpriteComp* art4Sprite = article_4->GetComponent<SpriteComp>();

    OpenSprite->SetAlpha(1);  // Open 버튼 표시
    storeSprite->SetAlpha(0);  // 상점 팝업 숨김
    CloseSprite->SetAlpha(0);  // Close 버튼 숨김
    art1Sprite->SetAlpha(0);   // 상품들 숨김
    art2Sprite->SetAlpha(0);
    art3Sprite->SetAlpha(0);
    art4Sprite->SetAlpha(0);
}

void InitStoreUI()
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
    OpenButton->SetOnClickFunction([]() {
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
    CloseButton->SetOnClickFunction([]() {
        Setoff();  // 상점 닫기
    });
    ButtonManager::GetInstance().RegisterButton(CloseButton);

    // Article 1 설정
    article_1 = new GameObject();
    article_1->AddComponent<SpriteComp>();
    article_1->AddComponent<TransformComp>();
    TransformComp* transArt1 = article_1->GetComponent<TransformComp>();
    transArt1->SetScale({ 150,150 });
    transArt1->SetPos({ 400, 100 });
    SpriteComp* art1Sprite = article_1->GetComponent<SpriteComp>();
    art1Sprite->SetTexture("Assets/arrow.png");
    art1Sprite->SetColor(250, 250, 0);
    art1Sprite->SetAlpha(0);
    article_1->AddComponent<ButtonComp>();
    ButtonComp* art1Button = article_1->GetComponent<ButtonComp>();
    art1Button->SetOnClickFunction([]() {
        // 상품 1 클릭 이벤트 추가
    });
    ButtonManager::GetInstance().RegisterButton(art1Button);

    // Article 2 설정
    article_2 = new GameObject();
    article_2->AddComponent<SpriteComp>();
    article_2->AddComponent<TransformComp>();
    TransformComp* transArt2 = article_2->GetComponent<TransformComp>();
    transArt2->SetScale({ 150,150 });
    transArt2->SetPos({ 400, -100 });
    SpriteComp* art2Sprite = article_2->GetComponent<SpriteComp>();
    art2Sprite->SetTexture("Assets/arrow.png");
    art2Sprite->SetColor(250, 250, 0);
    art2Sprite->SetAlpha(0);
    article_2->AddComponent<ButtonComp>();
    ButtonComp* art2Button = article_2->GetComponent<ButtonComp>();
    art2Button->SetOnClickFunction([]() {
        // 상품 2 클릭 이벤트 추가
    });
    ButtonManager::GetInstance().RegisterButton(art2Button);

    article_3 = new GameObject();
    article_3->AddComponent<SpriteComp>();
    article_3->AddComponent<TransformComp>();
    TransformComp* transArt3 = article_3->GetComponent<TransformComp>();
    transArt3->SetScale({ 150,150 });
    transArt3->SetPos({ 200, 100 });
    SpriteComp* art3Sprite = article_3->GetComponent<SpriteComp>();
    art3Sprite->SetTexture("Assets/arrow.png");
    art3Sprite->SetColor(250, 250, 0);
    art3Sprite->SetAlpha(0);
    article_3->AddComponent<ButtonComp>();
    ButtonComp* art3Button = article_3->GetComponent<ButtonComp>();
    art2Button->SetOnClickFunction([]() {
        // 상품 2 클릭 이벤트 추가
        });
    ButtonManager::GetInstance().RegisterButton(art3Button);

    article_4 = new GameObject();
    article_4->AddComponent<SpriteComp>();
    article_4->AddComponent<TransformComp>();
    TransformComp* transArt4 = article_4->GetComponent<TransformComp>();
    transArt4->SetScale({ 150,150 });
    transArt4->SetPos({ 200, -100 });
    SpriteComp* art4Sprite = article_4->GetComponent<SpriteComp>();
    art4Sprite->SetTexture("Assets/arrow.png");
    art4Sprite->SetColor(250, 250, 0);
    art4Sprite->SetAlpha(0);
    article_4->AddComponent<ButtonComp>();
    ButtonComp* art4Button = article_4->GetComponent<ButtonComp>();
    art2Button->SetOnClickFunction([]() {
        // 상품 2 클릭 이벤트 추가
        });
    ButtonManager::GetInstance().RegisterButton(art4Button);
}

void UpdateStoreUI()
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
