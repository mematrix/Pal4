#pragma once

#include "Skill/Enum/ESkillAttribute.h"

class ICharacterDelegate;


/**
 * ���ܴ������������������Ϣ
 */
struct PAL4_API FSkillTriggerInfo
{
    // �����ͷ���Դ
    ESkillSource Source;
    // ������
    ICharacterDelegate *Actor;
    // ����Ŀ��
    ICharacterDelegate *Target;
};
