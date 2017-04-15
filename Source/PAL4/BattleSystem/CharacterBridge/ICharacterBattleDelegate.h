#pragma once

#include <functional>

struct FBaseRestorerModel;
struct FBaseAttackModel;
struct FBaseStatusModel;
class IRoundActionHandler;
class ICharacterPropertyManager;
class FCharacterPersistentStatus;
class ICharacterRoundManager;
class ICharacterTemporaryStatus;

/*
 * ����ս��������ࡣ��Ϊһ��������ս�������У��ṩ���������Եķ��ʺ����ýӿڣ�
 * ͬʱ�ṩս����������Ҫ����Ϣ�ͻص����ƽӿ�
 */
class PAL4_API ICharacterBattleDelegate
{
public:
    virtual ~ICharacterBattleDelegate()
    {
    }

    virtual ICharacterPropertyManager& GetPropertyManager() = 0;

    virtual FCharacterPersistentStatus& GetPersistentStatus() = 0;

    virtual IRoundActionHandler& GetRoundAction() = 0;

    virtual void OnBattleBegin(const ICharacterRoundManager&, const ICharacterTemporaryStatus&) = 0;

    virtual void OnBattleFinished() = 0;

    virtual void OnStatusActionFinished(int32, const FBaseStatusModel&) = 0;

    virtual void BeInStatusAction(int32, const FBaseStatusModel&) = 0;

    virtual void OnAttackActionFinished(int32, const FBaseAttackModel&) = 0;

    virtual void BeInAttackAction(int32, const FBaseAttackModel&) = 0;

    virtual void OnRestorerActionFinished(int32, const FBaseRestorerModel&) = 0;

    virtual void BeInRestorerAction(int32, const FBaseRestorerModel&) = 0;


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
};
