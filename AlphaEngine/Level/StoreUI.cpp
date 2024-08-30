#include "StoreUI.h"

#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include <iostream>

GameObject* Openbtn = nullptr;
GameObject* StorePopup = nullptr;
GameObject* Closebtn = nullptr;
GameObject* article_1= nullptr;
GameObject* article_2 = nullptr;
GameObject* article_3 = nullptr;
GameObject* article_4 = nullptr;

void level::StoreUI::Init()
{
	Openbtn = new GameObject();
	Openbtn->AddComponent<SpriteComp>();
	Openbtn->AddComponent<AudioComp>();
	Openbtn->AddComponent<TransformComp>();
	TransformComp* transOpen = Openbtn->GetComponent<TransformComp>();
	transOpen->SetScale({ 50,50 });
	transOpen->SetPos({ 0, 320 });
	SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
	OpenSprite->SetTexture("Assets/arrow.png");
	OpenSprite->SetColor(250, 0, 255);

	StorePopup = new GameObject();
	StorePopup->AddComponent<SpriteComp>();
	StorePopup->AddComponent<AudioComp>();
	StorePopup->AddComponent<TransformComp>();
	TransformComp* transStore = StorePopup->GetComponent<TransformComp>();
	transStore->SetScale({ 1200,600 });
	transStore->SetPos({ 0, 0 });
	SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
	storeSprite->SetTexture("Assets/arrow.png");
	storeSprite->SetColor(255, 255, 255);

	Closebtn = new GameObject();
	Closebtn->AddComponent<SpriteComp>();
	Closebtn->AddComponent<AudioComp>();
	Closebtn->AddComponent<TransformComp>();
	TransformComp* transClose = Closebtn->GetComponent<TransformComp>();
	transClose->SetScale({ 50,50 });
	transClose->SetPos({ 550, 250 });
	SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
	CloseSprite->SetTexture("Assets/arrow.png");
	CloseSprite->SetColor(250, 0, 0);

	article_1 = new GameObject();
	article_1->AddComponent<SpriteComp>();
	article_1->AddComponent<AudioComp>();
	article_1->AddComponent<TransformComp>();
	TransformComp* transArt1 = article_1->GetComponent<TransformComp>();
	transArt1->SetScale({ 150,150 });
	transArt1->SetPos({ 400, 100 });
	SpriteComp* art1Sprite = article_1->GetComponent<SpriteComp>();
	art1Sprite->SetTexture("Assets/arrow.png");
	art1Sprite->SetColor(250, 250, 0);

	article_2 = new GameObject();
	article_2->AddComponent<SpriteComp>();
	article_2->AddComponent<AudioComp>();
	article_2->AddComponent<TransformComp>();
	TransformComp* transArt2 = article_2->GetComponent<TransformComp>();
	transArt2->SetScale({ 150,150 });
	transArt2->SetPos({ 400, -100 });
	SpriteComp* art2Sprite = article_2->GetComponent<SpriteComp>();
	art2Sprite->SetTexture("Assets/arrow.png");
	art2Sprite->SetColor(250, 250, 0);

	article_3 = new GameObject();
	article_3->AddComponent<SpriteComp>();
	article_3->AddComponent<AudioComp>();
	article_3->AddComponent<TransformComp>();
	TransformComp* transArt3 = article_3->GetComponent<TransformComp>();
	transArt3->SetScale({ 150,150 });
	transArt3->SetPos({ 200, -100 });
	SpriteComp* art3Sprite = article_3->GetComponent<SpriteComp>();
	art3Sprite->SetTexture("Assets/arrow.png");
	art3Sprite->SetColor(250, 250, 0);

	article_4 = new GameObject();
	article_4->AddComponent<SpriteComp>();
	article_4->AddComponent<AudioComp>();
	article_4->AddComponent<TransformComp>();
	TransformComp* transArt4 = article_4->GetComponent<TransformComp>();
	transArt4->SetScale({ 150,150 });
	transArt4->SetPos({ 200, 100 });
	SpriteComp* art4Sprite = article_4->GetComponent<SpriteComp>();
	art4Sprite->SetTexture("Assets/arrow.png");
	art4Sprite->SetColor(250, 250, 0);
}
void level::StoreUI::Update()
{
	s32 mouseX, mouseY;
	AEInputGetCursorPosition(&mouseX, &mouseY);

	// Assuming the screen coordinates are centered, adjust as needed
	mouseY = -mouseY + 450;
	mouseX =  mouseX - 800;
	TransformComp* TransClose = Closebtn->GetComponent<TransformComp>();
	SpriteComp* closeSprite = Closebtn->GetComponent<SpriteComp>();
	AEVec2 closePos = TransClose->GetPos();
	AEVec2 closeScale = TransClose->GetScale();

	if (mouseX > closePos.x - closeScale.x / 2 && mouseX < closePos.x + closeScale.x / 2 &&
		mouseY > closePos.y - closeScale.y / 2 && mouseY < closePos.y + closeScale.y / 2) {
		// Mouse is over the start button
		closeSprite->SetColor(100, 0, 0);  // Change color on hover

		if (AEInputCheckCurr(AEVK_LBUTTON)) {
			// Trigger start event (e.g., change game state)
			//StartGame();
			std::cout << "Closed" << std::endl;
		}
	}


	//TransformComp* transOpen = Openbtn->GetComponent<TransformComp>();
	//SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();


}
void level::StoreUI::Exit()
{

}