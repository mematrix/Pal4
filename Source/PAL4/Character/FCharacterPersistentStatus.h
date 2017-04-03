// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PAL4.h"
#include "Util/FlagBitUtil.h"

enum class PAL4_API ECommonBuff
{
    None = 0,
    // 镜，反弹普攻和特技
    ReboundAttackAndSkill = 1,
    // 壁，普通攻击无效
    InvalidateAttack = 2,
    // 界，法术攻击无效
    InvalidateMagic = 3,
    // 宁，吸收仙术伤害
    AbsorbMagicDamage = 4
};

enum class PAL4_API EPoison
{
    None = 0,
    // 水毒
    Water = 1,
    // 火毒
    Fire = 2,
    // 雷毒
    Thunder = 3,
    // 风毒
    Wind = 4,
    // 土毒
    Soil = 5
};

enum class PAL4_API EControlledDebuff
{
    None = 0,
    // 定，角色行动条停止，不可操作
    Root = 1,
    // 封，角色不可使用仙术
    SealMagic = 2,
    // 禁，角色不可使用物品或者逃跑
    BanProp = 3,
    // 眠，角色行动条停止
    Sleep = 4,
    // 狂，角色无法控制，不分敌我的进行普通攻击，攻击力加倍
    Crazy = 5,
    // 乱，角色无法控制，不分敌我，可使用任意技能、物品
    Chaos = 6
};

enum class PAL4_API ECharacterProperty : uint32
{
    // 武
    Attack = 1 << 0,
    // 运
    Luck = 1 << 1,
    // 灵
    Nimbus = 1 << 2,
    // 速
    Speed = 1 << 3,
    // 防
    Defence = 1 << 4,
    PropertyEnd
};

enum class PAL4_API ECharacterStatus
{
    // 常规属性
    Property,
    // 通用Buff
    CommonBuff,
    // 隐身状态
    Invisible,
    // “生”状态
    CanRevive,
    // 中毒属性
    Poison,
    // 控制性Debuff
    ControlledDebuff
};

constexpr int32 GetFlagLeastBitIndex(ECharacterProperty prop)
{
    return GetLeastBitIndex(static_cast<int32>(prop));
}

constexpr int32 CharacterPropertyEnumCount = GetLeastBitIndex(static_cast<int32>(ECharacterProperty::PropertyEnd) - 1) + 1;

template<typename... T>
class PAL4_API FCharacterPropertyStatus;

/**
 *
 */
template<typename... T>
class PAL4_API FCharacterStatusInfo
{
    friend class FCharacterPropertyStatus<T...>;

public:
    FCharacterStatusInfo() = default;
    FCharacterStatusInfo(FCharacterStatusInfo&&) = default;
    FCharacterStatusInfo(const FCharacterStatusInfo&) = delete;
    ~FCharacterStatusInfo() = default;

    FCharacterStatusInfo& operator= (FCharacterStatusInfo&&) = default;
    FCharacterStatusInfo& operator= (const FCharacterStatusInfo&) = delete;

public:
    int32 GetStatusValue(ECharacterStatus status) const
    {
        switch (status)
        {
        case ECharacterStatus::Property:
        {
            int32 ret = 0;
            uint32 mask = 1;
            for (int32 i = 0; i < CharacterPropertyEnumCount; ++i)
            {
                if (propertyTransformers[i].Num() > 0)
                {
                    ret |= mask;
                }
                mask <<= 1;
            }
            return ret;
        }

        case ECharacterStatus::CommonBuff:
            return static_cast<int32>(CommonBuff);

        case ECharacterStatus::Invisible:
            return static_cast<int32>(IsInvisible);

        case ECharacterStatus::CanRevive:
            return static_cast<int32>(CanRevive);

        case ECharacterStatus::Poison:
            return static_cast<int32>(Poison);

        case ECharacterStatus::ControlledDebuff:
            return static_cast<int32>(ControlledDebuff);
            
        default:
            return 0;
        }
    }

    const TMap<void*, int32(void*, ECharacterProperty, T...)>* GetPropertyTransformer(ECharacterProperty prop) const
    {
        switch (prop)
        {
        case ECharacterProperty::Attack:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Attack)];

        case ECharacterProperty::Luck:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Luck)];

        case ECharacterProperty::Nimbus:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Nimbus)];

        case ECharacterProperty::Speed:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Speed)];

        case ECharacterProperty::Defence:
            return &propertyTransformers[GetFlagLeastBitIndex(ECharacterProperty::Defence)];

        default:
            return nullptr;
        }
    }

private:
    void AddPropertyTransformer(uint32 props, const void* key, int32(*value)(void*, ECharacterProperty, T...))
    {
        for (int32 i = 0; i < CharacterPropertyEnumCount && props; ++i)
        {
            if (props & 0x01)
            {
                propertyTransformers[i].Add(key, value);
            }
            props >>= 1;
        }
    }

    void RemovePropertyTransformer(uint32 props, const void* key)
    {
        for (int32 i = 0; i < CharacterPropertyEnumCount && props; ++i)
        {
            if (props & 0x01)
            {
                propertyTransformers[i].Remove(key);
            }
            props >>= 1;
        }
    }

private:
    // 属性增益变换列表。存储了每一个可附加计算状态的属性的变换列表
    TMap<void*, int32(void*, ECharacterProperty, T...)> propertyTransformers[CharacterPropertyEnumCount];

    // Buff状态
    // 通用Buff：镜壁界宁
    ECommonBuff CommonBuff;
    // 中毒状态
    EPoison Poison;
    // 控制性Debuff
    EControlledDebuff ControlledDebuff;
    // 是否隐身状态
    bool IsInvisible;
    // 是否可在死亡后立即复活。“生”状态
    bool CanRevive;
};

// 用于存储持久化的状态信息，比如装备、被动技能带来的状态信息
using FPersistenceStatusInfo = FCharacterStatusInfo<int32>;
// 用于存储临时的状态信息，比如战斗中使用技能、仙术等附加的Buff
using FTemporaryStatusInfo = FCharacterStatusInfo<int32, int32>;
