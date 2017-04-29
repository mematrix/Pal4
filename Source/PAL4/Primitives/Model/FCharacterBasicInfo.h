#pragma once

#include <Platform.h>

#include "../EnumType/ERace.h"
#include "../EnumType/EPhysicalAttack.h"


struct PAL4_API FCharacterBasicInfo
{
    FCharacterBasicInfo(int32 id, const FName& name, ERace race, EPhysicalAttackType type, EPhysicalAttackTarget target)
        : ID(id),
        Name(name),
        Level(0),
        Experience(0),
        MaxHealthPoint(0),
        MaxManaPoint(0),
        MaxCraftPoint(0),
        HealthPoint(0),
        ManaPoint(0),
        CraftPoint(0),
        MagicPoints{0},
        Race(race),
        PhysicalAttackType(type),
        PhysicalAttackTarget(target)
    {
    }

    // ָʾ�Ƿ��������Ӫ�Ľ�ɫ
    //bool IsPlayer;
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    const int32 ID;
    // ��������
    const FName Name;

    // �ȼ�
    int32 Level;
    // ����ֵ�����������ǵ�ǰ�ȼ��ľ��飬���ڹ������Ǳ����ܺ�ɻ�ȡ�ľ���
    int32 Experience;
    
    // ������ֵ
    int32 MaxHealthPoint;
    // ������ֵ
    int32 MaxManaPoint;
    // ������ֵ
    int32 MaxCraftPoint;

    // ��
    int32 HealthPoint;
    // ��
    int32 ManaPoint;
    // ��
    int32 CraftPoint;

    // ��ϵ�������ܵ�
    uint8 MagicPoints[5];
    // ����
    const ERace Race;
    // ����������
    const EPhysicalAttackType PhysicalAttackType;
    // ������Ŀ��
    const EPhysicalAttackTarget PhysicalAttackTarget;
};
