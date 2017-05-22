#pragma once

#include <functional>
#include <map>

#include "FSkillResult.h"

class ICharacterCombatDelegate;


/**
 * ���ܻ��ࡣ������һ������ִ�еĻ�������
 */
class PAL4_API ISkill
{
public:
    virtual ~ISkill() = default;

    /**
     * ���㼼��ִ��Ԥ�ڽ�����˽����������ɺ����ܵ���������
     */
    virtual void ComputeResult(std::map<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult>&) = 0;

    virtual void BeforeAction() = 0;

    /**
     * ִ�м��ܹ��̡�����һ���ص��������˺����������������������ߡ������������Լ��˺�ģ�Ͷ���
     */
    virtual void DoAction(const std::map<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult>&,
        const std::function<void(ICharacterCombatDelegate&, ICharacterCombatDelegate&, const FSkillResult&)>&) = 0;

    virtual void AfterAction() = 0;
};
