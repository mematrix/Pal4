#pragma once

#include <vector>
#include <functional>

#include <Platform.h>
#include <SharedPointer.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/EnumType/ESkillTriggerType.h"


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


struct PAL4_API FTriggerResult
{
    // ���ܴ�������
    ESkillTriggerType TriggerType;
    // �����ص�����
};


struct PAL4_API FCombatStatusResult
{
    //
};


struct PAL4_API FSkillResult
{
    // ������Ϣ�����ͨ��Ϊ0��1�����ݣ�ֻ�зִ��˺�ʱ�Ż��ж������
    std::vector<FBasicInfoResult> BasicInfoResult;
    // ״̬��Ϣ�����ÿһ��״̬һ������
    std::vector<FStatusInfoResult> StatusInfoResult;
    // ������Ϣ�����ÿһ�����һ������
    std::vector<FTriggerResult> TriggerResult;
    // ս��Buff��Debuff������޸ı���Ϊnullptr
    TSharedPtr<FCombatStatusResult> CombatStatusResult;
};
