#pragma once

#include <functional>

#include <SharedPointer.h>

#include "BattleDelegate/RoundAction/IRoundAction.h"

class ICharacterBattleDelegate;


class PAL4_API FNormalAttackAction : public IRoundAction
{
public:
    typedef TSharedRef<TArray<std::reference_wrapper<ICharacterBattleDelegate>>> FTargetArray;

    FNormalAttackAction(ICharacterBattleDelegate& actor, const FTargetArray& targets, int32 count, int32 craftGrowth);

    void BeforeDoAction() override final;

    void DoAction() override final;

    void AfterDoAction() override final;

protected:
    virtual ICharacterBattleDelegate* PrepareHelp() { return nullptr; }

    virtual void FinishHelp() { }

    virtual void PrepareAttack() = 0;

    virtual void FinishAttack() = 0;

    /**
     * һ�ι���������Ļص���������ﵥ�ζ����������������ÿ��������������ص�����ʱcountInAction�����˵��ζ����еĹ�������
     * @param countOfAction �����ۻ�����������������
     * @param countInAction ���ζ����й���������ע�ⲻ���ܹ�������
     * @param target ����Ŀ��
     */
    virtual void OnOneAttackFinished(int32 countOfAction, int32 countInAction, ICharacterBattleDelegate& target) = 0;

    /**
     * �Ƿ�Ӧ�ü���������������
     */
    virtual bool CanAttackAgain() { return false; }

private:
    ICharacterBattleDelegate& Actor;
    FTargetArray Targets;

    // ��ͨ�����ֶδ��������纫��ɴһ����ͨ�����ᷢ�����ι�����
    int32 Count;
    // ÿ�ι���������
    int32 CraftGrowthValue;
    // Ԯ���ߡ�nullptr��ʾ��Ԯ����
    ICharacterBattleDelegate* Helper;
};
