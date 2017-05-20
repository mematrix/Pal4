#pragma once

#include <crtdbg.h>

#include <Delegate.h>

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterStatusProperty;
class ICharacterCombatContext;


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

    virtual ICharacterStatusProperty& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterCombatDelegate&, const FBaseStatusModel&, int32) = 0;

    /**
     * ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
     */
    virtual bool IsPlayer() const = 0;
    /**
     * ��ɫ�Ƿ���
     */
    virtual bool IsAlive() const = 0;
    /*
     * ��ȡ��ɫΨһID�����ڴ�ȫ�����ݼ��л�ȡ��ɫ��Ϣ������ͷ�����Ƶ�
     */
    virtual int32 GetId() const = 0;

    /**
     * ��ȡ��ɫ����ֵ
     */
    virtual int32 GetHealthValue() const = 0;
    /**
     * ��ȡ��ɫ�����Ե�ֵ
     */
    virtual int32 GetManaValue() const = 0;
    /**
     * ��ȡ��ɫ�����Ե�ֵ
     */
    virtual int32 GetCraftValue() const = 0;

    /**
     * ���ӻ���ٽ�ɫ����ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�����ֵ
     */
    virtual int32 AddHealthValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
     */
    virtual int32 AddManaValue(int32) = 0;
    /**
     * ���ӻ���ٽ�ɫ������ֵ��ֵΪ������ʾ���ӣ�������ʾ����
     * @return ʵ�����ӻ���ٵ�������ֵ
     */
    virtual int32 AddCraftValue(int32) = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterCombatContext* Context;
};
