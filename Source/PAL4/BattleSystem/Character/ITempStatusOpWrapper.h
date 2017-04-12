#pragma once

class FCharacterTempStatusManager;

class PAL4_API ITempStatusOpWrapper
{
public:
    virtual ~ITempStatusOpWrapper()
    {
    }

    virtual void OnAddingStatus(FCharacterTempStatusManager&) = 0;

    virtual void OnRemovingStatus(FCharacterTempStatusManager&) = 0;
};
