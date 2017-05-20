#pragma once

#include <functional>
#include <map>
#include <vector>

#include <Platform.h>

class ICharacterCombatDelegate;


class PAL4_API ISkill
{
public:
    virtual ~ISkill() = default;

    virtual void BeforeAction() = 0;

    // TODO: int32��Ҫ�滻Ϊ�˺����ݽṹ
    virtual void DoAction(const std::map<std::reference_wrapper<ICharacterCombatDelegate>, std::vector<int32>>&,
        const std::function<void(ICharacterCombatDelegate&, ICharacterCombatDelegate&, int32)>&) = 0;
};
