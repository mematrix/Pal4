#pragma once

#include <functional>
#include <list>

#include "FSkillResult.h"

class ICharacterCombatDelegate;


class PAL4_API ISkillActionCallback
{
public:
    virtual ~ISkillActionCallback() = default;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FBasicInfoResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FStatusInfoResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FTriggerResult&) = 0;

    virtual void ApplyResult(ICharacterCombatDelegate*, ICharacterCombatDelegate&, const FCombatStatusResult&) = 0;
};


/**
 * ���ܻ��ࡣ������һ������ִ�еĻ�������
 */
class PAL4_API ISkill
{
public:
    typedef std::pair<std::reference_wrapper<ICharacterCombatDelegate>, FSkillResult> ResultPair;

    virtual ~ISkill() = default;

    virtual int32 GetID() const = 0;

    // TODO: using enum as ret value
    virtual int32 GetType() const = 0;

    /**
     * ���㼼��ִ��Ԥ�ڽ�����˽����������ɺ����ܵ���������
     */
    virtual void ComputeResult(std::list<ResultPair>&) = 0;

    virtual void BeforeAction() = 0;

    /**
     * ִ�м��ܹ��̡�����һ���ص�����������ɼ��ܽ������
     */
    virtual void DoAction(const std::list<ResultPair>&, ISkillActionCallback&) = 0;

    virtual void AfterAction() = 0;

    /**
     * ���ӵļ��ܣ������ڵ�ǰ����@code ISkill::DoAction \endcode ���ý�����
     * @code ISkill::AfterAction \endcode ִ��֮ǰ������
     * ����nullptr��ʾ�޸��Ӽ���
     */
    virtual TSharedPtr<ISkill> AttachedSkill() = 0;
};
