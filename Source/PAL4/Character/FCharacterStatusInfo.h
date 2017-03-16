// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PAL4.h"
#include "Util/FlagBitUtil.h"

enum class PAL4_API ECommonBuff
{
    None = 0,
    // ���������չ����ؼ�
    ReboundAttackAndSkill = 1,
    // �ڣ���ͨ������Ч
    InvalidateAttack = 2,
    // �磬����������Ч
    InvalidateMagic = 3,
    // �������������˺�
    AbsorbMagicDamage = 4
};

enum class PAL4_API EPoison
{
    None = 0,
    // ˮ��
    Water = 1,
    // ��
    Fire = 2,
    // �׶�
    Thunder = 3,
    // �綾
    Wind = 4,
    // ����
    Soil = 5
};

enum class PAL4_API EControlledDebuff
{
    None = 0,
    // ������ɫ�ж���ֹͣ�����ɲ���
    Root = 1,
    // �⣬��ɫ����ʹ������
    SealMagic = 2,
    // ������ɫ����ʹ����Ʒ��������
    BanProp = 3,
    // �ߣ���ɫ�ж���ֹͣ
    Sleep = 4,
    // �񣬽�ɫ�޷����ƣ����ֵ��ҵĽ�����ͨ�������������ӱ�
    Crazy = 5,
    // �ң���ɫ�޷����ƣ����ֵ��ң���ʹ�����⼼�ܡ���Ʒ
    Chaos = 6
};

enum class PAL4_API ECharacterProperty : uint32
{
    // ��
    Attack = 1 << 0,
    // ��
    Luck = 1 << 1,
    // ��
    Nimbus = 1 << 2,
    // ��
    Speed = 1 << 3,
    // ��
    Defence = 1 << 4,
    PropertyEnd
};

enum class PAL4_API ECharacterStatus
{
    // ��������
    Property,
    // ͨ��Buff
    CommonBuff,
    // ����״̬
    Invisible,
    // ������״̬
    CanRevive,
    // �ж�����
    Poison,
    // ������Debuff
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
    // ��������任�б��洢��ÿһ���ɸ��Ӽ���״̬�����Եı任�б�
    TMap<void*, int32(void*, ECharacterProperty, T...)> propertyTransformers[CharacterPropertyEnumCount];

    // Buff״̬
    // ͨ��Buff�����ڽ���
    ECommonBuff CommonBuff;
    // �ж�״̬
    EPoison Poison;
    // ������Debuff
    EControlledDebuff ControlledDebuff;
    // �Ƿ�����״̬
    bool IsInvisible;
    // �Ƿ�����������������������״̬
    bool CanRevive;
};

// ���ڴ洢�־û���״̬��Ϣ������װ�����������ܴ�����״̬��Ϣ
using FPersistenceStatusInfo = FCharacterStatusInfo<int32>;
// ���ڴ洢��ʱ��״̬��Ϣ������ս����ʹ�ü��ܡ������ȸ��ӵ�Buff
using FTemporaryStatusInfo = FCharacterStatusInfo<int32, int32>;
