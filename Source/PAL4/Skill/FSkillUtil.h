#pragma once

#include "ISkill.h"


/**
 * һ�������࣬����ִ��һ�μ��ܣ�����������ܸ���������ִ�����񡣸������񳣼��ڸ��Ӽ��ܡ��������������ܵȣ�
 * ����@code ESkillTriggerType \endcode �������Ĵ�������
 */
class PAL4_API FSkillUtil
{
public:
    static void Execute(ISkill& skill);
};
