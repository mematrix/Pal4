#pragma once

class ICharacterDelegate;
class IRoundManager;
class ISkillReactor;
class IStatusManager;


/**
 * ��ɫ����ս������ʱ�������������Ϣ
 */
class PAL4_API ICombatContext
{
public:
    virtual ~ICombatContext() = default;

    /**
     * ��ȡ�����Ľ�ɫ�������
     */
    virtual ICharacterDelegate& GetCharacter() = 0;

    /**
     * ��ȡ��ɫ�����ĻغϹ������
     */
    virtual IRoundManager& GetRoundManager() = 0;

    /**
     * ��ȡ���ܱ���Ч�������������
     */
    virtual ISkillReactor& GetSkillReactor() = 0;

    /**
     * ��ȡ������ɫ��״̬�������
     */
    virtual IStatusManager& GetStatusManager() = 0;
};
