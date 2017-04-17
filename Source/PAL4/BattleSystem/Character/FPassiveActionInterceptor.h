#pragma once

class PAL4_API FPassiveActionInterceptor
{
public:
    void BeforeComputeStatusResult();

    void AfterComputeStatusResult();

    void AfterStatusAction();

    void BeforeComputeAttackResult();

    void AfterComputeAttackResult();

    void AfterAttackAction();

    void BeforeComputeRestorerResult();

    void AfterComputeRestorerResult();

    void AfterRestorerAction();
};
