#pragma once

/**
 * ��װһ���غϵĶ������������������������
 */
class PAL4_API IRoundAction
{
public:
    virtual ~IRoundAction() = default;

    virtual void BeforeDoAction() { }
    virtual void DoAction() = 0;
    virtual void AfterDoAction() { }
};
