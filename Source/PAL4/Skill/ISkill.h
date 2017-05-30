#pragma once

#include <functional>
#include <list>

#include "FSkillResult.h"

class ICharacterDelegate;


class PAL4_API ISkillActionCallback
{
public:
    virtual ~ISkillActionCallback() = default;

    virtual void ApplyBasicInfoResult(ICharacterDelegate*, ICharacterDelegate&, const FBasicInfoResult&) = 0;

    virtual void ApplyStatusInfoResult(ICharacterDelegate*, ICharacterDelegate&, const FStatusInfoResult&) = 0;

    virtual void ApplyTriggerResult(ICharacterDelegate*, ICharacterDelegate&, const FTriggerResult&) = 0;

    virtual void ApplyCombatStatusResult(ICharacterDelegate*, ICharacterDelegate&, const FCombatStatusResult&) = 0;
};


/**
 * ���ܻ��ࡣ������һ������ִ�еĻ�������
 */
class PAL4_API ISkill
{
public:
    typedef std::pair<std::reference_wrapper<ICharacterDelegate>, FSkillResult> ResultPair;

    virtual ~ISkill() = default;

    virtual int32 GetID() const = 0;

    /**
     * ��ȡ�������ԡ��������ԡ�����������
     */
    virtual uint32 GetAttribute() const = 0;

    /**
     * ��ȡ�����ߡ����˺���Դ�ļ��ܷ���nullptr
     */
    virtual ICharacterDelegate* GetActor() = 0;

    /**
     * �Ƿ���Դ����������߱�������
     */
    virtual bool CanTriggerPassiveSkill() const = 0;

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
     * @return ���Ӽ��ܡ�����nullptr��ʾ�޸��Ӽ���
     */
    virtual TSharedPtr<ISkill> AttachedSkill() = 0;
};
