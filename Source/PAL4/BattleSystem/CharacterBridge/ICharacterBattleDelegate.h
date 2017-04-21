#pragma once

#include <functional>

#include "Util/MacroUtil.h"

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class ISingleAction;
class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterBattleContext;

class ICharacterBattleDelegate;

template<typename Model>
struct PAL4_API ActionResultModel
{
    /**
    * ����ָʾֵ
    */
    int32 Type;
    /**
    * �����ͷ��ߣ������ߣ�
    */
    ICharacterBattleDelegate* Releaser;
    /**
    * ����Ŀ�꣨�������ߣ�
    */
    ICharacterBattleDelegate* Target;
    /**
    * ��������ģ�������
    */
    Model* ActionModel;
    /**
     * �Զ��帽������
     */
    void* Tag;
};

template ActionResultModel<FBaseStatusModel>;
template ActionResultModel<FBaseAttackModel>;
template ActionResultModel<FBaseRestorerModel>;

/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    ICharacterBattleDelegate() : Context(nullptr)
    {
    }

    MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(ICharacterBattleDelegate)

    virtual ~ICharacterBattleDelegate()
    {
    }

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
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnDeadCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
    /**
    * ���ý�ɫ����ʱ�Ļص���
    * @warning Ŀǰ������ @code ICharacterRoundDispatcher\endcode ��
    */
    virtual void SetOnReviveCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICharacterBattleContext* Context;
};
