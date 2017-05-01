#pragma once

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
};
