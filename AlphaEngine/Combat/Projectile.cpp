// Author : sinu

#include "Projectile.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"

bool Projectile::isLaunchProjectile = false;
const float ProjectileDelay = 0.001f;
float velocityX = 0, velocityY = 0;

Projectile::Projectile(GameObject* _owner) : LogicComponent(_owner), velocity(0), theta(0),
mass(1), time(0), delay(0), initialVelocity({ 0,0 }), wind({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::Projectile(GameObject* _owner, float velocity_value, float theta_value) 
    : LogicComponent(_owner), velocity(velocity_value), theta(theta_value),
    mass(1), time(0), delay(0), initialVelocity({ 0,0 }), wind({ 0,0 }), startY(0), projectile(nullptr)
{

}

Projectile::~Projectile()
{

}

// ������ �ٶ��� ����� ������ �����ϴ� �Լ� (����)
void Projectile::GenerateRandomWind(AEVec2& wind) {
    float windSpeed = (float)(std::rand() % ((WIND_MAX * 2) + 1) - WIND_MAX); // -50���� 50 ������ �ӵ�
    float windAngle = AEDegToRad((f32)(std::rand() % 180)) * (std::rand() % 2 == 0 ? -1 : 1); // 0���� 360�� ������ ������ �������� ��ȯ

    wind.x = windSpeed * std::cos(windAngle);
    wind.y = windSpeed * std::sin(windAngle);
}

void Projectile::CalculateProjectileMotion()
{
    initialVelocity.x = velocity * std::cos(theta);
    initialVelocity.y = velocity * std::sin(theta);
    mass = 1.f;
    time = 0.0f;
    GenerateRandomWind(wind);
    startY = projectile->GetComponent<TransformComp>()->GetPos().y;
}

void Projectile::Update()
{
    if (isLaunchProjectile)
    {
        TransformComp* ptf = projectile->GetComponent<TransformComp>();

        delay += static_cast<float>(AEFrameRateControllerGetFrameTime());

        // ����ü�� ���鿡 ��� ������ �ݺ�
        if (ptf->GetPos().y >= startY) {
            if (delay > ProjectileDelay)
            {
                // �ð� ����
                float timeStep = static_cast<float>(AEFrameRateControllerGetFrameTime());
                // ���� �ӵ� ��� (�ӵ��� ���� ���װ� �ٶ� ����)
                velocityX = initialVelocity.x + wind.x;
                velocityY = initialVelocity.y + wind.y;

                std::cout << " Wind x,y :"  << wind.x << ", " << wind.y << std::endl;

                float airResistanceX = -AIR_RESISTANCE_COEFFICIENT
                    * velocityX * std::abs(velocityX);// / mass;
                float airResistanceY = -AIR_RESISTANCE_COEFFICIENT
                    * velocityY * std::abs(velocityY);// / mass;

                // �ӵ��� ���� ���� ����
                velocityX += airResistanceX * time;
                velocityY += airResistanceY * time - GRAVITY * time;

                //std::cout << "Velocity x,y : " << velocityX << " , " << velocityY << std::endl;

                // ��ġ ������Ʈ
                float x = ptf->GetPos().x; // ����ü�� ��ġ ���� �� x
                float y = ptf->GetPos().y; // ����ü�� ��ġ ���� �� y

                ptf->SetPos({ x + velocityX * time, y + velocityY * time });

                // �ð� ����
                time += timeStep;


                delay = 0.f;
            }
            // ���� ������Ʈ
            ptf->SetRot(atan2f(velocityY, velocityX));

            //x = ptf->GetPos().x;
            //y = ptf->GetPos().y;
            //
            // ���� �ð�, ��ġ ���
            //std::cout << "Time: " << time << "s, X: " << x << "m, Y: " << y << 
            //    //"m, Wind: (" << wind.x << ", " << wind.y << ") m/s" 
            //    "value: " << velocityY
            //    << std::endl;
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
