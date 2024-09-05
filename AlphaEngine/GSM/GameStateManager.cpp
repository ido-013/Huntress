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
}

void GSM::GameStateManager::Update()
{
    if (currentLevel)
    {
        AEGfxSetBackgroundColor(0, 0, 0);

        ComponentManager<LogicComponent>::GetInstance().Update();
        ComponentManager<EngineComponent>::GetInstance().Update();

        ComponentManager<AudioComp>::GetInstance().Update();
        ComponentManager<LifetimeComp>::GetInstance().Update();
        ButtonManager::GetInstance().Update();
        EventManager::GetInstance().DispatchAllEvents();

        CollisionManager::GetInstance().Update();

        if (currentLevel)
            currentLevel->Update();
        ComponentManager<GraphicComponent>::GetInstance().Update();
    }
}

void GSM::GameStateManager::Exit()
{
    EventManager::GetInstance().DeleteUndispahchEvent();
    GameObjectManager::GetInstance().RemoveAllObject();
    ButtonManager::GetInstance().RemoveAllButtons();

    if (currentLevel)
    {
        currentLevel->Exit();
    }
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    Exit();
    delete currentLevel;

    //Exit the current level

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
