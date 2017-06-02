#pragma once

#include <functional>

#include <Delegate.h>

class ISingleAction;
class ICharacterDelegate;
struct FBaseStatusModel;
struct FBaseAttackModel;
struct FBaseRestorerModel;


class PAL4_API ISkillReactor
{
public:
    typedef std::function<TSharedRef<FBaseStatusModel>(
        ISkillReactor&, const ISingleAction&, const TSharedRef<FBaseStatusModel>&, int32)> FStatusInterceptorFunc;
    typedef std::function<TSharedRef<FBaseAttackModel>(
        ISkillReactor&, const ISingleAction&, const TSharedRef<FBaseAttackModel>&, int32)> FAttackInterceptorFunc;
    typedef std::function<TSharedRef<FBaseRestorerModel>(
        ISkillReactor&, const ISingleAction&, const TSharedRef<FBaseRestorerModel>&, int32)> FRestorerInterceptorFunc;

    DECLARE_EVENT_FourParams(ISkillReactor, FOnAttackActionFinishedEvent, const ISkillReactor&,
        const ISingleAction&, const FBaseAttackModel&, int32)
    DECLARE_EVENT_FourParams(ISkillReactor, FOnRestorerActionFinishedEvent, const ISkillReactor&,
        const ISingleAction&, const FBaseRestorerModel&, int32)
    DECLARE_EVENT_FourParams(ISkillReactor, FOnStatusActionFinishedEvent, const ISkillReactor&,
        const ISingleAction&, const FBaseStatusModel&, int32)

protected:
    mutable FOnAttackActionFinishedEvent OnAttackActionFinishedEvent;
    mutable FOnRestorerActionFinishedEvent OnRestorerActionFinishedEvent;
    mutable FOnStatusActionFinishedEvent OnStatusActionFinishedEvent;

public:
    explicit ISkillReactor(ICharacterDelegate& character) :
        Character(character)
    {
    }
    ISkillReactor(const ISkillReactor&) = default;
    ISkillReactor(ISkillReactor&&) = default;

    virtual ~ISkillReactor() = default;

    ISkillReactor& operator=(const ISkillReactor&) = default;
    ISkillReactor& operator=(ISkillReactor&&) = default;

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
