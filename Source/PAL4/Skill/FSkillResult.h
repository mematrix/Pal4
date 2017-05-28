#pragma once

#include <vector>
#include <functional>

#include <Platform.h>
#include <SharedPointer.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/EnumType/ESkillTriggerType.h"
#include "Primitives/EnumType/ECombatStatus.h"
#include "Primitives/EnumType/EAttackSpecialStatus.h"

class ICharacterDelegate;


/**
 * ����������Ϣ�������񣩱仯�������ֵΪ���ӣ���ֵΪ����
 */
struct PAL4_API FBasicInfoResult
{
    // ���仯��
    int32 HealthValue;
    // ��仯��
    int32 ManaValue;
    // ���仯��
    int32 CraftValue;
    // �쳣״̬���������ܸ�
    EAttackSpecialStatus SpecialStatus;
};


/**
 * ����״̬��Ϣ�任���
 */
struct PAL4_API FStatusInfoResult
{
    // ����״̬����
    ECharacterStatusType StatusType;
    // ״̬�任����
    std::function<int32(int32)> TransformAction;
    // ��Ч�غ�����0��ʾ������Ч
    uint32 ValidRoundNum;
};


/**
 * �������ͽ����Ϣ
 */
struct PAL4_API FTriggerResult
{
    // ���ܴ�������
    ESkillTriggerType TriggerType;
    // �����ص�����
    std::function<void(ICharacterDelegate&, ICharacterDelegate&)> TriggerFunc;
};


/**
 * ս��״̬�����Ϣ
 */
struct PAL4_API FCombatStatusResult
{
    // ս��״̬���ͣ�Buff��Debuff
    ECombatStatus StatusType;
    // ս��״ֵ̬����������ȡ��Ӧֵ
    union
    {
        EBuff Buff;
        EPoison Poison;
        EDebuff Debuff;
        bool CanResurrect;
        bool Invisible;
    } Status;
    // ״̬Ч���������غ���
    uint32 MaxEffectRoundNum;
};


/**
 * �����ͷŽ������
 */
struct PAL4_API FSkillResult
{
    // ������Ϣ�����ͨ��Ϊ0��1�����ݣ�ֻ�зִ��˺�ʱ�Ż��ж������
    TSharedPtr<std::vector<FBasicInfoResult>> BasicInfoResult;
    // ״̬��Ϣ�����ÿһ��״̬һ������
    TSharedPtr<std::vector<FStatusInfoResult>> StatusInfoResult;
    // ������Ϣ�����ÿһ�����һ������
    TSharedPtr<std::vector<FTriggerResult>> TriggerResult;
    // ս��Buff��Debuff������޸ı���Ϊnullptr
    TSharedPtr<FCombatStatusResult> CombatStatusResult;
};
