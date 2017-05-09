#pragma once

#include <string>

#include <Platform.h>


/**
 * ������Ϣ
 */
struct PAL4_API FMagicData
{
    // ����ID
    int32 ID;
    // ��������
    std::string Name;
    // ����˵��
    std::string Description;
    // Ч��˵��
    std::string EffectDescription;

    // AIָ������
    uint8 AICommandType;
    // �����Ƿ���ڷ�ս�����ʹ��
    uint8 CanUseInSystem;
    // ������������
    uint8 ActType;
    // ����Ŀ��
    uint8 TargetType;
    // ��������
    uint8 WulingType;
    // ������������Ҫ�ڸ�ϵ�е�����������
    uint8 PreviaMagicPoint;
    // ѧϰ�����������������
    uint8 StudyMagicPoint;
    // ����ϰ�õ�ǰ�ü���ID
    int32 PreviaSkillID;

    // ���Ӽ���ID
    int32 SkillID;
    // ������ֵ
    int32 ManaConsumeValue;

    // ʩ���߶���ID
    int32 ActorActionID;
    // Ŀ�귽��ЧID
    int32 TargetEffectID;
    // Ŀ�귽��Ч���ص�
    uint8 TargetEffectPos;
};
