#pragma once

#include <functional>

#include <Delegate.h>

class ISingleAction;
class ICharacterCombatDelegate;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;


class PAL4_API IPassiveActionInterceptor
{
public:
    typedef std::function<TSharedRef<FBaseStatusModel>(
        IPassiveActionInterceptor&, const ISingleAction&, const TSharedRef<FBaseStatusModel>&, int32)> FStatusInterceptorFunc;
    typedef std::function<TSharedRef<FBaseAttackModel>(
        IPassiveActionInterceptor&, const ISingleAction&, const TSharedRef<FBaseAttackModel>&, int32)> FAttackInterceptorFunc;
    typedef std::function<TSharedRef<FBaseRestorerModel>(
        IPassiveActionInterceptor&, const ISingleAction&, const TSharedRef<FBaseRestorerModel>&, int32)> FRestorerInterceptorFunc;

    DECLARE_EVENT_FourParams(IPassiveActionInterceptor, FOnAttackActionFinishedEvent, const IPassiveActionInterceptor&,
        const ISingleAction&, const FBaseAttackModel&, int32)
    DECLARE_EVENT_FourParams(IPassiveActionInterceptor, FOnRestorerActionFinishedEvent, const IPassiveActionInterceptor&,
        const ISingleAction&, const FBaseRestorerModel&, int32)
    DECLARE_EVENT_FourParams(IPassiveActionInterceptor, FOnStatusActionFinishedEvent, const IPassiveActionInterceptor&,
        const ISingleAction&, const FBaseStatusModel&, int32)

protected:
    mutable FOnAttackActionFinishedEvent OnAttackActionFinishedEvent;
    mutable FOnRestorerActionFinishedEvent OnRestorerActionFinishedEvent;
    mutable FOnStatusActionFinishedEvent OnStatusActionFinishedEvent;

public:
    explicit IPassiveActionInterceptor(ICharacterDelegate& character) :
        Character(character)
    {
    }
    IPassiveActionInterceptor(const IPassiveActionInterceptor&) = default;
    IPassiveActionInterceptor(IPassiveActionInterceptor&&) = default;

    virtual ~IPassiveActionInterceptor() = default;

    IPassiveActionInterceptor& operator=(const IPassiveActionInterceptor&) = default;
    IPassiveActionInterceptor& operator=(IPassiveActionInterceptor&&) = default;

    FOnAttackActionFinishedEvent& OnAttackActionFinished() const { return OnAttackActionFinishedEvent; }
    FOnRestorerActionFinishedEvent& OnRestorerActionFinished() const { return OnRestorerActionFinishedEvent; }
    FOnStatusActionFinishedEvent& OnStatusActionFinished() const { return OnStatusActionFinishedEvent; }

    ICharacterDelegate& GetCharacter() const { return Character; }

    virtual FStatusInterceptorFunc SetStatusInterceptor(const FStatusInterceptorFunc&) = 0;
    virtual FAttackInterceptorFunc SetAttackInterceptor(const FAttackInterceptorFunc&) = 0;
    virtual FRestorerInterceptorFunc SetRestorerInterceptor(const FRestorerInterceptorFunc&) = 0;

private:
    ICharacterDelegate& Character;
};
