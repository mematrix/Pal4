#pragma once

class FBattleCharacter;

class PAL4_API ITempStatusOpWrapper
{
public:
    virtual ~ITempStatusOpWrapper()
    {
    }

    virtual void OnAddingStatus(FBattleCharacter&) = 0;

    virtual void OnRemovingStatus(FBattleCharacter&) = 0;
};
