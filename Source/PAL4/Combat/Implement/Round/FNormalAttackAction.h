#pragma once

#include <functional>

#include <SharedPointer.h>

#include "Combat/Interface/Round/IRoundAction.h"

class ICharacterDelegate;


class PAL4_API FNormalAttackAction : public IRoundAction
{
public:
    typedef TSharedRef<TArray<std::reference_wrapper<ICharacterDelegate>>> FTargetArray;

    FNormalAttackAction(ICharacterDelegate& actor, const FTargetArray& targets, int32 count, int32 craftGrowth);

    void BeforeDoAction() override final;

    void DoAction() override final;

    void AfterDoAction() override final;

protected:
    virtual ICharacterDelegate* PrepareHelp() { return nullptr; }

    virtual void FinishHelp() { }

    virtual void PrepareAttack() = 0;

    virtual void FinishAttack() = 0;

    /**
     * һ�ι���������Ļص���������ﵥ�ζ����������������ÿ��������������ص�����ʱcountInAction�����˵��ζ����еĹ�������
     * @param countOfAction �����ۻ�����������������
     * @param countInAction ���ζ����й���������ע�ⲻ���ܹ�������
     * @param target ����Ŀ��
     */
    virtual void OnOneAttackFinished(int32 countOfAction, int32 countInAction, ICharacterDelegate& target) = 0;

    /**
     * �Ƿ�Ӧ�ü���������������
     */
    virtual bool CanAttackAgain() { return false; }

private:
    ICharacterDelegate& Actor;
    FTargetArray Targets;

    // ��ͨ�����ֶδ��������纫��ɴһ����ͨ�����ᷢ�����ι�����
    int32 Count;
    // ÿ�ι���������
    int32 CraftGrowthValue;
    // Ԯ���ߡ�nullptr��ʾ��Ԯ����
    ICharacterDelegate* Helper;
};
