#pragma once


/*
 * AI指令类型
 */
enum class PAL4_API EAICommandType
{
    // 攻击
    Attack,
    // 辅助
    Auxiliary,
    // 恢复
    Restore,
    // 被动
    Reactive,
    // 召唤
    Calling,
    // 复活
    Resurrection,
    // 不可用
    Unavailable
};
