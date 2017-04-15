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
 * 人物战斗代理基类。作为一个代理，在战斗过程中，提供对人物属性的访问和设置接口；
 * 同时提供战斗过程中需要的信息和回调控制接口
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
    * 设置角色死亡时的回调。
    * @warning 目前仅用于 @code ICharacterRoundDispatcher\endcode 中
    */
    virtual void SetOnDeadCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
    /**
    * 设置角色复活时的回调。
    * @warning 目前仅用于 @code ICharacterRoundDispatcher\endcode 中
    */
    virtual void SetOnReviveCallback(std::function<void(const ICharacterBattleDelegate&)>) = 0;
};
