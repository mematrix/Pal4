#pragma once

#include "ICharacterTempStatusOperator.h"


class PAL4_API ITempStatusOpWrapper
{
public:
    virtual ~ITempStatusOpWrapper()
    {
    }

    virtual void OnAddingStatus(ICharacterTempStatusOperator&) = 0;

    virtual void OnRemovingStatus(ICharacterTempStatusOperator&) = 0;
};
