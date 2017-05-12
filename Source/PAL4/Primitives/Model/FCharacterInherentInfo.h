#pragma once

#include <string>

#include <NameTypes.h>

#include "Primitives/EnumType/ERace.h"
#include "Primitives/EnumType/EPhysicalAttack.h"


struct PAL4_API FCharacterInherentInfo
{
    // ��ɫID�����ڻ�ȡȫ����Ϣ���������ơ�ͷ���
    int32 ID;
    // ��������
    FName Name;

    // ����
    ERace Race;
    // ����������
    EPhysicalAttackType PhysicalAttackType;
    // ������Ŀ��
    EPhysicalAttackTarget PhysicalAttackTarget;

    // ��άͼ��
    int32 IconID2D;
    // ��άģ�ͱ��
    int32 ModelID3D;
    // ��ά��ͼ���
    int32 MapID3D;
    // ������Ч1
    std::string InjuredSound1;
    // ������Ч2
    std::string InjuredSound2;
    // ������Ч3
    std::string InjuredSound3;
};
