#pragma once

class ICharacterDelegate;
class IRoundManager;
class ISkillReactor;
class IStatusManager;


/**
 * 角色处于战斗场景时的相关上下文信息
 */
class PAL4_API ICombatContext
{
public:
    virtual ~ICombatContext() = default;

    /**
     * 获取关联的角色代理对象
     */
    virtual ICharacterDelegate& GetCharacter() = 0;

    /**
     * 获取角色关联的回合管理对象
     */
    virtual IRoundManager& GetRoundManager() = 0;

    /**
     * 获取技能被动效果触发处理对象
     */
    virtual ISkillReactor& GetSkillReactor() = 0;

    /**
     * 获取关联角色的状态管理对象
     */
    virtual IStatusManager& GetStatusManager() = 0;
};
