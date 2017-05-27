#pragma once

#include <functional>

#include <Platform.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/EnumType/ECombatStatus.h"


/**
 * 人物状态属性及战斗状态管理。状态属性类型枚举见@code ECharacterStatusType \endcode
 */
class PAL4_API IStatusManager
{
public:
    virtual ~IStatusManager() = default;


    /**
     * @brief 设置状态变换函数
     * @param skillID 触发技能ID，如果无，传入默认值0
     * @param type 状态影响属性类型
     * @param validNum 临时状态有效回合数
     * @param func 变换函数
     */
    virtual void SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func) = 0;

    /**
     * @brief 清除指定技能的所有状态变换函数
     * @param skillID 技能ID
     */
    virtual void ClearSkillStatus(int32 skillID) = 0;

    /**
     * @brief 清除指定类型的状态变换函数
     * @param type 属性类型
     */
    virtual void ClearSpecialStatus(ECharacterStatusType type) = 0;

    /**
     * @brief 清除状态变换函数
     * @param skillID 设置状态的技能ID
     * @param type 状态影响属性类型
     */
    virtual void ClearStatus(int32 skillID, ECharacterStatusType type) = 0;

    /**
     * @brief 设置Buff。镜壁界宁
     * @param buff Buff类型
     * @param maxRoundNum 状态最长有效回合数
     */
    virtual void SetBuff(EBuff buff, uint32 maxRoundNum) = 0;

    /**
     * @brief 设置中毒状态。五毒互斥
     * @param poison 五毒类型
     * @param maxRoundNum 状态最长有效回合数
     */
    virtual void SetPoison(EPoison poison, uint32 maxRoundNum) = 0;

    /**
     * @brief 设置Debuff。定禁眠狂乱
     * @param debuff Debuff类型
     * @param maxRoundNum 状态最长有效回合数
     */
    virtual void SetDebuff(EDebuff debuff, uint32 maxRoundNum) = 0;

    /**
     * @brief 设置“生”状态。生状态下，可复活一次
     * @param canResurrct 是否附加“生”状态
     * @param maxRoundNum 状态最长有效回合数
     */
    virtual void SetResurrect(bool canResurrct, uint32 maxRoundNum) = 0;

    /**
     * @brief 设置隐身状态
     * @param invisible 是否隐身
     * @param maxRoundNum 状态最长有效回合数
     */
    virtual void SetInvisible(bool invisible, uint32 maxRoundNum) = 0;
};
