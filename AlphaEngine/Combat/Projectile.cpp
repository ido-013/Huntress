// Author : sinu

#include "../Utils/Size.h"
#include "Projectile.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"

AEVec2 Projectile::wind = { 0.f, 0.f };
bool Projectile::isLaunchProjectile = false;
const float ProjectileDelay = 0.001f;
float velocityX = 0, velocityY = 0;

Projectile::Projectile(GameObject* _owner) : LogicComponent(_owner), velocity(0), theta(0),
mass(1), time(0), delay(0), initialVelocity({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::Projectile(GameObject* _owner, float velocity_value, float theta_value) 
    : LogicComponent(_owner), velocity(velocity_value), theta(theta_value),
    mass(1), time(0), delay(0), initialVelocity({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::~Projectile()
{
}

// 랜덤한 바람의 세기와 방향을 생성하는 함수 (라디안)
void Projectile::GenerateRandomWind(AEVec2& wind) {
    float wSpeed = (float)(std::rand() % ((WIND_MAX * 2) + 1) - WIND_MAX); // -50에서 50 사이의 속도
    float wAngle = AEDegToRad((f32)(std::rand() % 180)) * (std::rand() % 2 == 0 ? -1 : 1); // 0에서 360도 사이의 방향을 라디안으로 변환

    GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
    directionArrow->GetComponent<CombatComp>()->data.windPower = wSpeed;
    directionArrow->GetComponent<CombatComp>()->data.windAngle = wAngle;

    wind.x = wSpeed * std::cos(wAngle);
    wind.y = wSpeed * std::sin(wAngle);
}

void Projectile::CalculateProjectileMotion()
{
    initialVelocity.x = velocity * std::cos(theta);
    initialVelocity.y = velocity * std::sin(theta);
    mass = 1.f;
    time = 0.0f;
    if(CombatComp::turn == CombatComp::PLAYERTURN)
        GenerateRandomWind(Projectile::wind);
}

void Projectile::Update()
{
    if (isLaunchProjectile)
    {
        TransformComp* ptf = projectile->GetComponent<TransformComp>();

        delay += static_cast<float>(AEFrameRateControllerGetFrameTime());

        // 투사체가 화면 끝에 닿기 전까지 반복
        if (ptf->GetPos().y >= -windowWidthHalf) {
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

                // 시간 증가
                time += timeStep;

                delay = 0.f;
            }
            // 방향 업데이트
            ptf->SetRot(atan2f(velocityY, velocityX));
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
