#pragma once

#include <Delegate.h>

#include "Util/MacroUtil.h"
#include "CharacterPrimitives/Model/ECharacterBasicType.h"

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterBattleContext;


/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    DECLARE_EVENT_TwoParams(ICharacterBattleDelegate, FOnPropertyChangedEvent, const ICharacterBattleDelegate&, ECharacterBasicType)
    DECLARE_EVENT_OneParam(ICharacterBattleDelegate, FOnCharacterDeadEvent, const ICharacterBattleDelegate&)
    DECLARE_EVENT_OneParam(ICharacterBattleDelegate, FOnCharacterReviveEvent, const ICharacterBattleDelegate&)

protected:
    FOnPropertyChangedEvent OnPropertyChangedEvent;
    FOnCharacterDeadEvent OnCharacterDeadEvent;
    FOnCharacterReviveEvent OnCharacterReviveEvent;

public:
    ICharacterBattleDelegate() : Context(nullptr)
    {
    }

    MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(ICharacterBattleDelegate)

    virtual ~ICharacterBattleDelegate() = default;

    FOnPropertyChangedEvent& OnPropertyChanged() { return OnPropertyChangedEvent; }
    FOnCharacterDeadEvent& OnCharacterDead() { return OnCharacterDeadEvent; }
    FOnCharacterReviveEvent& OnCharacterRevive() { return OnCharacterReviveEvent; }

    void BeginBattle(ICharacterBattleContext& context)
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

    ICharacterBattleContext* GetContext() const { return Context; }

    virtual ICharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterPersistentStatus& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnAttackActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseAttackModel&, int32) = 0;

    virtual void OnRestorerActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseRestorerModel&, int32) = 0;

    virtual void OnStatusActionFinished(const ISingleAction&, const ICharacterBattleDelegate&, const FBaseStatusModel&, int32) = 0;

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

    /**
     * ��ȡָ�������������Ե���
     * @return ָ��ϵ���������Ե���
     */
    virtual int32 GetMagicPoint(EMagicCategory) = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterBattleContext* Context;
};
