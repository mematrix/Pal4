#pragma once

#include <Platform.h>

#include "Skill/Enum/ESkillType.h"
#include "Skill/Enum/ESkillTriggerType.h"
#include "Skill/Enum/ESkillAttribute.h"


struct PAL4_API FSkillInfo
{
    int32 ID;
    // �������ս�����ܡ���ͼ���ܵ�
    ESkillType Type;
    // ���ܴ�������
    ESkillTriggerType TriggerType;
    // ������Դ���ؼ����������߱���������
    ESkillSource Source;
    // �����������ࡣ���������ָ���
    ESkillCategory Category;
};
