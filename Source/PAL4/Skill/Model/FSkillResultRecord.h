#pragma once

#include "Skill/FSkillResult.h"


struct PAL4_API FBasicInfoResultRecord
{
    // ������Ϣ������ǿձ�֤
    FBasicInfoResult *Result;
    // �����ߡ�����Ϊnullptr
    ICharacterDelegate *Actor;
    // ����Ŀ�ꡣ��֤��nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FStatusInfoResultRecord
{
    // ״̬��Ϣ������ǿձ�֤
    FStatusInfoResult *Result;
    // �����ߡ�����Ϊnullptr
    ICharacterDelegate *Actor;
    // ����Ŀ�ꡣ��֤��nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FTriggerResultRecord
{
    // ������Ϣ������ǿձ�֤
    FTriggerResult *Result;
    // �����ߡ�����Ϊnullptr
    ICharacterDelegate *Actor;
    // ����Ŀ�ꡣ��֤��nullptr
    ICharacterDelegate *Target;
};


struct PAL4_API FCombatStatusResultRecord
{
    // ս��״̬��Ϣ������ǿձ�֤
    FCombatStatusResult *Result;
    // �����ߡ�����Ϊnullptr
    ICharacterDelegate *Actor;
    // ����Ŀ�ꡣ��֤��nullptr
    ICharacterDelegate *Target;
};
