#include "GameStateManager.h"
#include "AEEngine.h"
#include "../Level/BaseLevel.h"
#include "../ComponentManager/ComponentManager.h"
#include "../EventManager/EventManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Serializer/Serializer.h"
#include "../RTTI/Registry.h"
#include "../UIM/BtnManager.h"
#include "../Components/SubtitleComp.h"
#include "../Camera/Camera.h"
#include "../Weather/Weather.h"

GSM::GameStateManager::GameStateManager() : previousLevel(nullptr), currentLevel(nullptr) {}

GSM::GameStateManager::~GameStateManager()
{
    if (previousLevel)
        delete previousLevel;

    if (currentLevel)
        delete currentLevel;
}

void GSM::GameStateManager::Init()
{
    if (currentLevel)
    {
        currentLevel->Init();
    }
    if (CombatComp::state != CombatComp::STATE::STORE)
    {
        CombatComp::ResetCombat();
    }
    SubtitleComp::InitFont("Assets/DePixelKlein.ttf", 72);

}

void GSM::GameStateManager::Update()
{
    if (currentLevel)
    {
        AEGfxSetBackgroundColor(0, 0, 0);

        Camera::GetInstance().Update();

        ComponentManager<LogicComponent>::GetInstance().Update();
        ComponentManager<EngineComponent>::GetInstance().Update();

        ComponentManager<AudioComp>::GetInstance().Update();
        ComponentManager<LifetimeComp>::GetInstance().Update();
        CollisionManager::GetInstance().Update();
        EventManager::GetInstance().DispatchAllEvents();
        ButtonManager::GetInstance().Update();
    

        if (currentLevel)
            currentLevel->Update();

        ComponentManager<GraphicComponent>::GetInstance().Update();
        ComponentManager<InterfaceComponent>::GetInstance().Update();
        SubtitleComp::Update();
    
    }
}

void GSM::GameStateManager::Exit()
{
    if (currentLevel)
    {
        currentLevel->Exit();
    }
    SubtitleComp::DestroyFont();
    EventManager::GetInstance().DeleteUndispahchEvent();
    GameObjectManager::GetInstance().RemoveAllObject();
    ButtonManager::GetInstance().RemoveAllButtons();
    ResourceManager::GetInstance().UnloadAllResource();
    Weather::GetInstance().ClearWeather();
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    delete previousLevel;
    previousLevel = currentLevel;

    //Exit the current level
    Exit();

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
