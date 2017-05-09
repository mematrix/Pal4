#pragma once

#include <string>

#include <Platform.h>


/**
 * ������Ϣ
 */
struct PAL4_API FStuntData
{
    // �ؼ�ID
    int32 ID;
    // �ؼ�����
    std::string Name;
    // �ؼ�˵��
    std::string Description;
    // Ч��˵��
    std::string EffectDescription;

    // AIָ������
    uint8 AICommandType;
    // ������������
    uint8 ActType;
    // �ȼ�����
    uint8 LimitLevel;
    // �ؼ�ʹ�õ�����
    uint8 Weapon;

    // ���Ӽ���ID
    int32 SkillID;
    // ������ֵ
    int32 CraftConsumeValue;

    // ������Ʒ1ID
    int32 ConsumeProp1ID;
    // ������Ʒ1����
    int32 ConsumeProp1Count;
    // ������Ʒ2ID
    int32 ConsumeProp2ID;
    // ������Ʒ2����
    int32 ConsumeProp2Count;
    // ������Ʒ3ID
    int32 ConsumeProp3ID;
    // ������Ʒ3����
    int32 ConsumeProp3Count;
    // ������Ʒ4ID
    int32 ConsumeProp4ID;
    // ������Ʒ4����
    int32 ConsumeProp4Count;
    // ������Ʒ5ID
    int32 ConsumeProp5ID;
    // ������Ʒ5����
    int32 ConsumeProp5Count;
    // ���Ľ�Ǯ����
    int32 ConsumeMoneyCount;

    // ����ӵ�е���ƷID
    int32 RequiredPropID;
    // ����Я���ļ���ID
    int32 RequiredSkillID;

    // ʩ���߶���ID
    int32 ActorActionID;
    // Ŀ�귽��ЧID
    int32 TargetEffectID;
    // Ŀ�귽��Ч���ص�
    uint8 TargetEffectPos;
};
