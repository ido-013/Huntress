// Author : sinu

#include "../Utils/Size.h"
#include "Projectile.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/EnemyComp.h"
#include "../Components/PlayerComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../EventManager/EventManager.h"
#include "../Particle/Particle.h"
#include "../Camera/Camera.h"

AEVec2 Projectile::wind = { 0.f, 0.f };
float Projectile::windSpeed = 0.f;
float Projectile::windAngle = 0.f;
bool Projectile::isLaunchProjectile = false;
const float ProjectileDelay = 0.001f;
float velocityX = 0, velocityY = 0;

Projectile::Projectile(GameObject* _owner) : LogicComponent(_owner), launchTime(0), velocity(0), theta(0),
mass(1), time(0), delay(0), initialVelocity({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::Projectile(GameObject* _owner, float velocity_value, float theta_value) 
    : LogicComponent(_owner), launchTime(0), velocity(velocity_value), theta(theta_value),
    mass(1), time(0), delay(0), initialVelocity({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::~Projectile()
{
}

// 랜덤한 바람의 세기와 방향을 생성하는 함수 (라디안)
void Projectile::GenerateRandomWind() {
    windSpeed = (float)(std::rand() % ((WIND_MAX) + 1));
    windAngle = AEDegToRad((f32)(std::rand() % 180)) * (std::rand() % 2 == 0 ? -1 : 1); // 0에서 360도 사이의 방향을 라디안으로 변환

    GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
    directionArrow->GetComponent<CombatComp>()->data.windPower = windSpeed;
    directionArrow->GetComponent<CombatComp>()->data.windAngle = windAngle;

    Projectile::wind.x = windSpeed * std::cos(windAngle);
    Projectile::wind.y = windSpeed * std::sin(windAngle);
}

void Projectile::CalculateProjectileMotion()
{
    initialVelocity.x = velocity * std::cos(theta);
    initialVelocity.y = velocity * std::sin(theta);
    mass = 1.f;
    time = 0.0f;
}

void Projectile::UpdateCollision()
{
    GameObject* player = GameObjectManager::GetInstance().GetObj("player");
    PlayerComp* pComp = player->GetComponent<PlayerComp>();
    Data::PlayerData* pData = pComp->playerData;

    GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
    EnemyComp* eComp = enemy->GetComponent<EnemyComp>();
    Data::EnemyData* eData = enemy->GetComponent<EnemyComp>()->enemyData;

    GameObject* direction = GameObjectManager::GetInstance().GetObj("directionArrow");
    Data::CombatData* dData = &direction->GetComponent<CombatComp>()->data;
    
    TransformComp* ptf = player->GetComponent<TransformComp>();
    TransformComp* etf = enemy->GetComponent<TransformComp>();

    while (!oppoTypeQueue.empty())
    {
        if (CombatComp::turn == CombatComp::PLAYERTURN && oppoTypeQueue.front() == GameObject::Enemy)
        {
            colState = 1;

            // enemy hp update
            // dice
            int randomDamage = 1 + (rand() % 6);
            int randomArmor = 1 + (rand() % 6);
            float totalDmg = (pData->damage + randomDamage) - (eData->armor + randomArmor);
            if (totalDmg <= 0)
                totalDmg = 1;
            dData->randomValue1 = randomDamage;
            dData->randomValue2 = randomArmor;

#ifdef _DEBUG
            std::cout << "totalDmg before adding launchTime : " << totalDmg << std::endl;
#endif
            if (launchTime < TIME_ARANGE_1)
                totalDmg *= 1;
            else if (launchTime < TIME_ARANGE_2)
                totalDmg *= 1.5;
            else if (launchTime < TIME_ARANGE_3)
                totalDmg *= 2;
            else if (launchTime < TIME_ARANGE_4)
                totalDmg *= 3;
            else if (launchTime < TIME_ARANGE_5)
                totalDmg *= 4;
            else
                totalDmg *= 5;

#ifdef _DEBUG
            std::cout << "totalDmg after adding launchTime : " << totalDmg << std::endl;
#endif
            //eData->hp -= max(0, totalDmg);
            eComp->AddHp(-max(0, totalDmg));

            // particle
            Particle p(5, 2, (int)totalDmg, { 255, 0, 0 });
            p.PlayParticle(etf->GetPos().x, etf->GetPos().y);
         
            break;
        }

        else if (CombatComp::turn == CombatComp::ENEMYTURN && oppoTypeQueue.front() == GameObject::Player)
        {
            colState = 1;

            // player hp update
            // dice
            int randomDamage = 1 + (rand() % 6);
            int randomArmor = 1 + (rand() % 6);
            float totalDmg = (eData->damage + randomDamage) - (pData->armor + randomArmor);
            dData->randomValue1 = randomArmor;
            dData->randomValue2 = randomDamage;

            //pData->hp -= max(0, totalDmg);
            pComp->AddHp(-max(0, totalDmg));

            // particle
            Particle p(5, 2, (int)totalDmg, { 255, 0, 0 });
            p.PlayParticle(ptf->GetPos().x, ptf->GetPos().y);
 
            break;
        }

        else if (colState == 0 &&
            (oppoTypeQueue.front() == GameObject::Square || oppoTypeQueue.front() == GameObject::LeftTri || oppoTypeQueue.front() == GameObject::RightTri))
        {
            colState = 2;
        }

        else if (colState == -1 &&
            CombatComp::turn == CombatComp::PLAYERTURN && oppoTypeQueue.front() == GameObject::Player)
        {
            colState = 0;
        }

        else if (colState == -1 &&
            CombatComp::turn == CombatComp::ENEMYTURN && oppoTypeQueue.front() == GameObject::Enemy)
        {
            colState = 0;
        }

        oppoTypeQueue.pop();
    }
}

void Projectile::Update()
{
    if (isLaunchProjectile)
    {
        TransformComp* ptf = projectile->GetComponent<TransformComp>();
        ColliderComp* pc = projectile->GetComponent<ColliderComp>();

        delay += static_cast<float>(AEFrameRateControllerGetFrameTime());
        launchTime += static_cast<float>(AEFrameRateControllerGetFrameTime());
#ifdef _DEBUG
        //std::cout << "launchTime : " << launchTime << std::endl;
#endif
        AEVec2 p = GameObjectManager::GetInstance().GetObj("player")->GetComponent<TransformComp>()->GetPos();
        AEVec2 e = GameObjectManager::GetInstance().GetObj("enemy")->GetComponent<TransformComp>()->GetPos();
        // 투사체가 화면 끝에 닿기 전까지 반복
        if (ptf->GetPos().y >= MAP_BOTTOM_MAX && colState < 1) {
            if (delay > ProjectileDelay)
            {
                // 시간 간격
                float timeStep = static_cast<float>(AEFrameRateControllerGetFrameTime());
                // 현재 속도 계산 (속도에 공기 저항과 바람 적용)
                velocityX = initialVelocity.x + wind.x;
                velocityY = initialVelocity.y + wind.y;

                //std::cout << " Wind x,y :"  << wind.x << ", " << wind.y << std::endl;

                float airResistanceX = -AIR_RESISTANCE_COEFFICIENT
                    * velocityX * std::abs(velocityX);// / mass;
                float airResistanceY = -AIR_RESISTANCE_COEFFICIENT
                    * velocityY * std::abs(velocityY);// / mass;

                // 속도에 공기 저항 적용
                velocityX += airResistanceX * time;
                velocityY += airResistanceY * time - GRAVITY * time;

                //std::cout << "Velocity x,y : " << velocityX << " , " << velocityY << std::endl;

                // 위치 업데이트
                float x = ptf->GetPos().x; // 투사체의 위치 벡터 중 x
                float y = ptf->GetPos().y; // 투사체의 위치 벡터 중 y

                ptf->SetPos({ x + velocityX * time, y + velocityY * time });
                pc->SetPos({ x + velocityX * time, y + velocityY * time });

                // 카메라 업데이트
                //AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
                Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);

                // 시간 증가
                time += timeStep;

                delay = 0.f;
            }
            // 방향 업데이트
            ptf->SetRot(atan2f(velocityY, velocityX));

            UpdateCollision();
        }
        else
        {
            isLaunchProjectile = false;
            projectile->GetComponent<SpriteComp>()->SetAlpha(0);
            GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
            directionArrow->GetComponent<CombatComp>()->isDrawDirection = false;
            directionArrow->GetComponent<CombatComp>()->InitEnemyValue();
            directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
            CombatComp::turn = CombatComp::TurnChange();

            for (int i = 0; i < CombatComp::ArrowCount; i++)
            {
                GameObjectManager::GetInstance().RemoveObject(GameObjectManager::GetInstance().GetObj("projectile"));
            }
            EventManager::GetInstance().DeleteUndispahchEvent();
            CombatComp::ArrowCount = 0;
        }
    }
}

void Projectile::LoadFromJson(const json& data)
{
    auto compData = data.find("compData");

    if (compData != data.end())
    {
    }
}

json Projectile::SaveToJson()
{
    json data;
    data["type"] = TypeName;

    json compData;
    data["compData"] = compData;

    return data;
}

BaseRTTI* Projectile::CreateCombatComponent(GameObject* owner)
{
    BaseRTTI* p = new Projectile(owner);
    owner->AddComponent<Projectile>(static_cast<Projectile*>(p));
    return p;
}
