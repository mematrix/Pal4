#pragma once

/**
 * 封装一个回合的动作：攻、术、技、物、防、逃
 */
class PAL4_API IRoundAction
{
public:
    virtual ~IRoundAction() = default;

    virtual void BeforeDoAction() { }
    virtual void DoAction() = 0;
    virtual void AfterDoAction() { }
};
