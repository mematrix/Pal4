#pragma once

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

enum class PAL4_API ECharacterBattleStatus
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
