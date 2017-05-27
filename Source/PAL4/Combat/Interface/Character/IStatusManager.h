#pragma once

#include <functional>

#include <Platform.h>

#include "Primitives/EnumType/ECharacterStatusType.h"
#include "Primitives/EnumType/ECombatStatus.h"


/**
 * ����״̬���Լ�ս��״̬����״̬��������ö�ټ�@code ECharacterStatusType \endcode
 */
class PAL4_API IStatusManager
{
public:
    virtual ~IStatusManager() = default;


    /**
     * @brief ����״̬�任����
     * @param skillID ��������ID������ޣ�����Ĭ��ֵ0
     * @param type ״̬Ӱ����������
     * @param validNum ��ʱ״̬��Ч�غ���
     * @param func �任����
     */
    virtual void SetStatusTransform(int32 skillID, ECharacterStatusType type, uint32 validNum, const std::function<int32(int32)>& func) = 0;

    /**
     * @brief ���ָ�����ܵ�����״̬�任����
     * @param skillID ����ID
     */
    virtual void ClearSkillStatus(int32 skillID) = 0;

    /**
     * @brief ���ָ�����͵�״̬�任����
     * @param type ��������
     */
    virtual void ClearSpecialStatus(ECharacterStatusType type) = 0;

    /**
     * @brief ���״̬�任����
     * @param skillID ����״̬�ļ���ID
     * @param type ״̬Ӱ����������
     */
    virtual void ClearStatus(int32 skillID, ECharacterStatusType type) = 0;

    /**
     * @brief ����Buff�����ڽ���
     * @param buff Buff����
     * @param maxRoundNum ״̬���Ч�غ���
     */
    virtual void SetBuff(EBuff buff, uint32 maxRoundNum) = 0;

    /**
     * @brief �����ж�״̬���嶾����
     * @param poison �嶾����
     * @param maxRoundNum ״̬���Ч�غ���
     */
    virtual void SetPoison(EPoison poison, uint32 maxRoundNum) = 0;

    /**
     * @brief ����Debuff�������߿���
     * @param debuff Debuff����
     * @param maxRoundNum ״̬���Ч�غ���
     */
    virtual void SetDebuff(EDebuff debuff, uint32 maxRoundNum) = 0;

    /**
     * @brief ���á�����״̬����״̬�£��ɸ���һ��
     * @param canResurrct �Ƿ񸽼ӡ�����״̬
     * @param maxRoundNum ״̬���Ч�غ���
     */
    virtual void SetResurrect(bool canResurrct, uint32 maxRoundNum) = 0;

    /**
     * @brief ��������״̬
     * @param invisible �Ƿ�����
     * @param maxRoundNum ״̬���Ч�غ���
     */
    virtual void SetInvisible(bool invisible, uint32 maxRoundNum) = 0;
};
