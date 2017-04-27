#pragma once

#include <Platform.h>

#include "../EnumType/ERace.h"
#include "../EnumType/EPhysicalAttack.h"


struct PAL4_API FCharacterBasicInfo
{
    // ָʾ�Ƿ��������Ӫ�Ľ�ɫ
    //bool IsPlayer;
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    int32 ID;
    // ��������
    FName Name;

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
    ERace Race;
    // ����������
    EPhysicalAttackType PhysicalAttackType;
    // ������Ŀ��
    EPhysicalAttackTarget PhysicalAttackTarget;
};
