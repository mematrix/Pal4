#pragma once

#include <SharedPointer.h>

class ISkill;
class ICharacterDelegate;


class PAL4_API FSkillFactory
{
public:
    TSharedPtr<ISkill> CreateTriggerSkill(int32 skillID, ICharacterDelegate* actor, ICharacterDelegate& target);
};
