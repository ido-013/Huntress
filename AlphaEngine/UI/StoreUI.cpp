//#include "StoreUI.h"
//
//void SetStoreUI()
//{
//	isStore = true;
//	SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
//	OpenSprite->SetAlpha(0);
//	SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
//	SpriteComp*
//}
//
//void Setoff()
//{
//	isStore = false;
//
//
//}
//
//void InitStoreUI()
//{
//	if (!isStore) {
//		Openbtn = new GameObject();
//		Openbtn->AddComponent<SpriteComp>();
//		Openbtn->AddComponent<TransformComp>();
//		TransformComp* transOpen = Openbtn->GetComponent<TransformComp>();
//		transOpen->SetScale({ 50,50 });
//		transOpen->SetPos({ 0, 320 });
//		SpriteComp* OpenSprite = Openbtn->GetComponent<SpriteComp>();
//		OpenSprite->SetTexture("Assets/arrow.png");
//		OpenSprite->SetColor(250, 0, 255);
//		OpenSprite->SetAlpha(1);
//		Openbtn->AddComponent<ButtonComp>();
//		ButtonComp* OpenButton = Openbtn->GetComponent<ButtonComp>();
//		OpenButton->SetOnClickFunction([]
//			{
//				isStore = true;
//			});
//		ButtonManager::GetInstance().RegisterButton(OpenButton);
//	}
//	else {
//		StorePopup = new GameObject();
//		StorePopup->AddComponent<SpriteComp>();
//		StorePopup->AddComponent<TransformComp>();
//		TransformComp* transStore = StorePopup->GetComponent<TransformComp>();
//		transStore->SetScale({ 1200,600 });
//		transStore->SetPos({ 0, 0 });
//		SpriteComp* storeSprite = StorePopup->GetComponent<SpriteComp>();
//		storeSprite->SetTexture("Assets/arrow.png");
//		storeSprite->SetColor(255, 255, 255);
//		storeSprite->SetAlpha(0);
//
//
//		Closebtn = new GameObject();
//		Closebtn->AddComponent<SpriteComp>();
//		Closebtn->AddComponent<TransformComp>();
//		TransformComp* transClose = Closebtn->GetComponent<TransformComp>();
//		transClose->SetScale({ 50,50 });
//		transClose->SetPos({ 550, 250 });
//		SpriteComp* CloseSprite = Closebtn->GetComponent<SpriteComp>();
//		CloseSprite->SetTexture("Assets/arrow.png");
//		CloseSprite->SetColor(250, 0, 0);
//		CloseSprite->SetAlpha(0);
//		Closebtn->AddComponent<ButtonComp>();
//		ButtonComp* CloseButton = Closebtn->GetComponent<ButtonComp>();
//		CloseButton->SetOnClickFunction([]
//			{
//				//Add Event Maybe set alpha & active;
//			});
//		ButtonManager::GetInstance().RegisterButton(CloseButton);
//
//
//
//		article_1 = new GameObject();
//		article_1->AddComponent<SpriteComp>();
//		article_1->AddComponent<TransformComp>();
//		TransformComp* transArt1 = article_1->GetComponent<TransformComp>();
//		transArt1->SetScale({ 150,150 });
//		transArt1->SetPos({ 400, 100 });
//		SpriteComp* art1Sprite = article_1->GetComponent<SpriteComp>();
//		art1Sprite->SetTexture("Assets/arrow.png");
//		art1Sprite->SetColor(250, 250, 0);
//		art1Sprite->SetAlpha(0);
//		article_1->AddComponent<ButtonComp>();
//		ButtonComp* art1Button = article_1->GetComponent<ButtonComp>();
//		art1Button->SetOnClickFunction([]
//			{
//				//Add Event Maybe set alpha & active;
//			});
//		ButtonManager::GetInstance().RegisterButton(art1Button);
//
//
//
//		article_2 = new GameObject();
//		article_2->AddComponent<SpriteComp>();
//		article_2->AddComponent<TransformComp>();
//		TransformComp* transArt2 = article_2->GetComponent<TransformComp>();
//		transArt2->SetScale({ 150,150 });
//		transArt2->SetPos({ 400, -100 });
//		SpriteComp* art2Sprite = article_2->GetComponent<SpriteComp>();
//		art2Sprite->SetTexture("Assets/arrow.png");
//		art2Sprite->SetColor(250, 250, 0);
//		art2Sprite->SetAlpha(0);
//		article_2->AddComponent<ButtonComp>();
//		ButtonComp* art2Button = article_2->GetComponent<ButtonComp>();
//		art2Button->SetOnClickFunction([]
//			{
//				//Add Event Maybe set alpha & active;
//			});
//		ButtonManager::GetInstance().RegisterButton(art2Button);
//
//		article_3 = new GameObject();
//		article_3->AddComponent<SpriteComp>();
//		article_3->AddComponent<TransformComp>();
//		TransformComp* transArt3 = article_3->GetComponent<TransformComp>();
//		transArt3->SetScale({ 150,150 });
//		transArt3->SetPos({ 200, -100 });
//		SpriteComp* art3Sprite = article_3->GetComponent<SpriteComp>();
//		art3Sprite->SetTexture("Assets/arrow.png");
//		art3Sprite->SetColor(250, 250, 0);
//		art3Sprite->SetAlpha(0);
//		ButtonComp* art3Button = article_3->GetComponent<ButtonComp>();
//		art3Button->SetOnClickFunction([]
//			{
//				//Add Event Maybe set alpha & active;
//			});
//		ButtonManager::GetInstance().RegisterButton(art3Button);
//
//
//		article_4 = new GameObject();
//		article_4->AddComponent<SpriteComp>();
//		article_4->AddComponent<TransformComp>();
//		TransformComp* transArt4 = article_4->GetComponent<TransformComp>();
//		transArt4->SetScale({ 150,150 });
//		transArt4->SetPos({ 200, 100 });
//		SpriteComp* art4Sprite = article_4->GetComponent<SpriteComp>();
//		art4Sprite->SetTexture("Assets/arrow.png");
//		art4Sprite->SetColor(250, 250, 0);
//		art4Sprite->SetAlpha(0);
//		ButtonComp* art4Button = article_4->GetComponent<ButtonComp>();
//		art4Button->SetOnClickFunction([]
//			{
//				isStore = false;
//			});
//		ButtonManager::GetInstance().RegisterButton(art4Button);
//	}
//}
//void UpdateStoreUI()
//{
//	
//}
//void ExitStoreUI()
//{
//	
//}