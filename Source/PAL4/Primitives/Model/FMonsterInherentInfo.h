#pragma once

#include <NameTypes.h>

#include "../EnumType/EAIType.h"


struct PAL4_API FMonsterInherentInfo
{
    // 怪物信息描述
    FName Description;
    // 是否Boss
    bool IsBoss;
    // AI操作类型
    EAIType AIType;
    // 拥有技能列表。0代表无技能
    int32 SkillIDList[6];
    // AI操作时技能使用概率递增数组，以10000为基数计算百分比。
    // 数组值是单调非递减的，相邻两个值构成一个左闭右开的区间，其中第一个值与0构成技能1的概率。
    // 区间不存在的情况（比如[20, 20)这样的)表示技能不会被使用（也就是技能ID为0，不存在）。
    // 最后一位始终为10000，代表普通攻击。
    int32 SkillUsingProbability[7];
    // 可偷窃物品ID。注：物品ID为金钱ID时代表可偷窃金钱。
    // 因为仙剑四数据库中数据显示没有怪物可以同时偷窃到金钱与物品，因此此处将其合并了
    int32 StealPropID;
    // 偷窃物品数量。对于金钱来说就是偷窃金钱数
    int32 StealPropCount;
    // 掉落物品ID列表
    int32 DropPropIDList[4];
    // 掉落物品概率。以10000为基数计算百分比。每个物品概率都是独立的
    int32 DropPropProbability[4];
    // 掉落金钱最小值
    int32 DropMoneyMinValue;
    // 掉落金钱最大值
    int32 DropMoneyMaxValue;
    // 气初始化值
    int32 CraftInitPoint;
};
