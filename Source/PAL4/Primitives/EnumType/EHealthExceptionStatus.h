#pragma once


/*
 * 人物生命异常状态
 */
enum class PAL4_API EHealthExceptionStatus
{
    // 无异常
    None,
    // 虚弱
    Weak,
    // 濒死
    NearDeath,
    // 死亡
    Death
};
