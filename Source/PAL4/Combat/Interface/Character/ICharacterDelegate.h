#pragma once

#include <crtdbg.h>

#include <Platform.h>

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterStatus;
class ICombatContext;
class ICharacterProperty;


/**
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterDelegate
{
public:
    ICharacterDelegate() : Context(nullptr)
    {
    }

    ICharacterDelegate(const ICharacterDelegate&) = default;
    ICharacterDelegate(ICharacterDelegate&&) = default;
    
    ICharacterDelegate& operator=(const ICharacterDelegate&) = default;
    ICharacterDelegate& operator=(ICharacterDelegate&&) = default;

    virtual ~ICharacterDelegate() = default;


    void BeginBattle(ICombatContext& context)
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

    ICombatContext* GetContext() const { return Context; }

    virtual ICharacterProperty& GetProperty() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
     */
    virtual bool IsPlayer() const = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICombatContext* Context;
};
