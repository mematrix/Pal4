#pragma once

// 物理攻击方式
enum class PAL4_API EPhysicalAttackType : unsigned char
{
    // 近战
    Near = 0,
    // 远程
    Far
};

// 物理攻击目标
enum class PAL4_API EPhysicalAttackTarget : unsigned char
{
    // 单体
    Single = 0,
    // 全体
    All
};
