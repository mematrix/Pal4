#pragma once

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterStatusProperty;
class ICharacterCombatContext;
class ICharacterProperty;


/**
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterCombatDelegate
{
public:
    ICharacterCombatDelegate() : Context(nullptr)
    {
    }

    ICharacterCombatDelegate(const ICharacterCombatDelegate&) = default;
    ICharacterCombatDelegate(ICharacterCombatDelegate&&) = default;
    
    ICharacterCombatDelegate& operator=(const ICharacterCombatDelegate&) = default;
    ICharacterCombatDelegate& operator=(ICharacterCombatDelegate&&) = default;

    virtual ~ICharacterCombatDelegate() = default;


    void BeginBattle(ICharacterCombatContext& context)
    {
        _ASSERT(!Context);
        Context = &context;
        OnBattleBegin();
    }

    void FinishBattle()
    {
        OnBattleFinished();
        Context = nullptr;
    }

    ICharacterCombatContext* GetContext() const { return Context; }

    virtual ICharacterProperty& GetProperty() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
     */
    virtual bool IsPlayer() const = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterCombatContext* Context;
};
