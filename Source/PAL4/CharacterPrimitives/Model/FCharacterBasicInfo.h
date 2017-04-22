#pragma once

#include <Platform.h>

struct PAL4_API FCharacterBasicInfo
{
    // ָʾ�Ƿ��������Ӫ�Ľ�ɫ
    bool IsPlayer;

    // �ȼ�
    int32 Level;
    // ����ֵ
    int32 Experience;
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    int32 ID;
    
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
    unsigned char MagicPoints[5];
};
