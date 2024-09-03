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
#include "../Utils/Dice.h"

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

// ������ �ٶ��� ����� ������ �����ϴ� �Լ� (����)
void Projectile::GenerateRandomWind(AEVec2& wind) {
    float wSpeed = (float)(std::rand() % ((WIND_MAX * 2) + 1) - WIND_MAX); // -50���� 50 ������ �ӵ�
    float wAngle = AEDegToRad((f32)(std::rand() % 180)) * (std::rand() % 2 == 0 ? -1 : 1); // 0���� 360�� ������ ������ �������� ��ȯ

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

void Projectile::UpdateCollision()
{
    Particle p(5, 2, 5, { 255, 0, 0 });

    GameObject* player = GameObjectManager::GetInstance().GetObj("player");
    Data::PlayerData pData = player->GetComponent<PlayerComp>()->data;

    GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
    Data::EnemyData eData = enemy->GetComponent<EnemyComp>()->data;
    
    TransformComp* ptf = player->GetComponent<TransformComp>();
    TransformComp* etf = enemy->GetComponent<TransformComp>();

    while (!oppoTypeQueue.empty())
    {
        if (CombatComp::turn == CombatComp::PLAYERTURN && oppoTypeQueue.front() == GameObject::Enemy)
        {
            colState = 1;

            // enemy hp update
            // dice
            int res = PerformRoll();
            int first = res / 10;
            int second = res % 10;

            float totalDmg = (pData.damage + first) - (eData.armor + second);

            eData.hp -= max(0, totalDmg);
            
            // particle
            
            p.PlayParticle(etf->GetPos().x, etf->GetPos().y);

            break;
        }

        else if (CombatComp::turn == CombatComp::ENEMYTURN && oppoTypeQueue.front() == GameObject::Player)
        {
            colState = 1;

            // player hp update
            // dice
            int res = PerformRoll();
            int first = res / 10;
            int second = res % 10;

            float totalDmg = (eData.damage + first) - (pData.armor + second);

            pData.hp -= max(0, totalDmg);

            // particle
            
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

        delay += static_cast<float>(AEFrameRateControllerGetFrameTime());

        // ����ü�� ȭ�� ���� ��� ������ �ݺ�
        if (ptf->GetPos().y >= -windowWidthHalf && colState < 1) {
            if (delay > ProjectileDelay)
            {
                // �ð� ����
                float timeStep = static_cast<float>(AEFrameRateControllerGetFrameTime());
                // ���� �ӵ� ��� (�ӵ��� ���� ���װ� �ٶ� ����)
                velocityX = initialVelocity.x + wind.x;
                velocityY = initialVelocity.y + wind.y;

                //std::cout << " Wind x,y :"  << wind.x << ", " << wind.y << std::endl;

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

                // ī�޶� ������Ʈ
                AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);

                // �ð� ����
                time += timeStep;

                delay = 0.f;
            }
            // ���� ������Ʈ
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
