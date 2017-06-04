#pragma once

#include <crtdbg.h>

class ICombatContext;
class ICharacterProperty;
class IRoundActionHandler;


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

    /**
     * ��ɫ�Ƿ�������ҿ��Ƶ�һ����true��ʾ���һ����false��ʾ�з�����AI���
     */
    virtual bool IsPlayer() const = 0;

    /**
     * ��ȡ��ɫ���ԡ������ɫΪ��ҿ������ʵ�ʷ���@code IRoleProperty \endcode ����
     * ������ɫΪAIʱ������@code IMonsterProperty \endcode ����
     */
    virtual ICharacterProperty& GetProperty() = 0;

    /**
     * ��ȡ�غ϶����������
     */
    virtual IRoundActionHandler& GetRoundAction() = 0;

protected:
    virtual void OnBattleBegin() = 0;

    virtual void OnBattleFinished() = 0;

private:
    ICombatContext* Context;
};
