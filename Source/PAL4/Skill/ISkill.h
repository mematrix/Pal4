#pragma once

#include <functional>
#include <list>

#include "Model/FSkillResultRecord.h"

class ICharacterDelegate;
struct FSkillInfo;


class PAL4_API ISkillActionCallback
{
public:
    virtual ~ISkillActionCallback() = default;

    virtual void ApplyBasicInfoResult(const FBasicInfoResultRecord&) = 0;

    virtual void ApplyStatusInfoResult(const FStatusInfoResultRecord&) = 0;

    virtual void ApplyTriggerResult(const FTriggerResultRecord&) = 0;

    virtual void ApplyCombatStatusResult(const FCombatStatusResultRecord&) = 0;
};


/**
 * ���ܻ��ࡣ������һ������ִ�еĻ�������
 */
class PAL4_API ISkill
{
public:
    typedef std::pair<std::reference_wrapper<ICharacterDelegate>, FSkillResult> ResultPair;

    virtual ~ISkill() = default;

    /**
     * ��ȡ���ܻ�����Ϣ
     */
    virtual const FSkillInfo& GetInfo() const = 0;

    /**
     * ��ȡ�������ԡ��������ԡ�����������
     */
    virtual uint32 GetAttribute() const = 0;

    /**
     * ��ȡ�����ߡ����˺���Դ�ļ��ܷ���nullptr
     */
    virtual ICharacterDelegate* GetActor() = 0;

    /**
     * ���㼼��ִ��Ԥ�ڽ�����˽����������ɺ����ܵ���������
     */
    virtual void ComputeResult(std::list<ResultPair>&) = 0;

    /**
     * ִ��ǰ�ද��
     */
    virtual void BeforeAction() = 0;

    /**
     * ִ�м��ܹ��̡�����һ���ص�����������ɼ��ܽ������
     */
    virtual void DoAction(const std::list<ResultPair>&, ISkillActionCallback&) = 0;

    /**
     * ִ�к��ö���
     */
    virtual void AfterAction() = 0;

    /**
     * ���ӵļ��ܣ������ڵ�ǰ����@code ISkill::DoAction \endcode ���ý�����
     * @code ISkill::AfterAction \endcode ִ��֮ǰ������
     * @return ���Ӽ��ܡ�����nullptr��ʾ�޸��Ӽ���
     */
    virtual TSharedPtr<ISkill> AttachedSkill() = 0;
};
