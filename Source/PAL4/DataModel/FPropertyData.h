#pragma once

#include <string>

#include <Platform.h>


/**
 * 物品数据
 */
struct PAL4_API FPropertyData
{
    // 物品ID
    int32 ID;
    // 物品名称
    std::string Name;
    // 物品信息描述
    std::string Description;
    // 物品属性说明
    std::string EffectDescription;

    // 物品类型
    uint8 Class;
    // 道具等级
    uint8 Level;
    // 目标
    uint8 Target;
    // AI指令类型
    uint8 AICommandType;
    // 天河是否可以使用
    bool CanUseByTianhe;
    // 菱纱是否可以使用
    bool CanUseByLingsha;
    // 梦璃是否可以使用
    bool CanUseByMengli;
    // 紫英是否可以使用
    bool CanUseByZiying;

    // 金钱价格
    int32 Price;
    // 挂载技能ID
    int32 SkillID;
    // 是否可以丢弃出售
    bool CanSell;
    // 是否可以在系统中使用（即非战斗情况使用）
    bool CanUseInSystem;
    // 投掷类型
    uint8 ThrowType;
    // 效果开始计算时间：0表示从我方回合开始时为触发节点，1表示我方回合结束（即敌方回合开始）时为计算节点
    uint8 EffectStartTime;

    // 二维图标
    int32 IconID2D;
    // 三维模型编号
    int32 ModelID3D;
    // 三维贴图编号
    int32 MapID3D;
};
