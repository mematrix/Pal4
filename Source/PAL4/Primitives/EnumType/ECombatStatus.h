#pragma once


// 2017-04-29更新：使用拼音，汉语的单字表达的意思实在不好找到匹配而简洁的英文描述
enum class PAL4_API ECommonBuff
{
    None = 0,
    // 镜，反弹普攻和特技。ReboundAttackAndSkill
    Jing = 1,
    // 壁，普通攻击无效。InvalidateAttack
    Bi = 2,
    // 界，法术攻击无效。InvalidateMagic
    Jie = 3,
    // 宁，吸收仙术伤害。AbsorbMagicDamage
    Ning = 4
};

/**
 * 五毒。
 * 水毒:主角头像产生蓝色。
 * 火毒:主角头像产生红色。
 * 土毒:主角头像产生灰色。
 * 雷毒:主角头像产生紫色。
 * 风毒:主角头像产生绿色。
 */
enum class PAL4_API EPoison
{
    None = 0,
    // 水毒。使用任何仙术，物品或特技，都无法使中毒者回复“精”
    Water = 1,
    // 火毒。中毒者每回合减少一定比例的“精”
    Fire = 2,
    // 雷毒。中毒者发动普通攻击时，减少自身的“精”
    Thunder = 3,
    // 风毒。中毒者每回合减少一定比例的“神”
    Wind = 4,
    // 土毒。使用任何物品都无法使中毒者回复“神”
    Soil = 5
};

enum class PAL4_API EControlledDebuff
{
    None = 0,
    // 定，角色处于不可操作状态
    Root = 1,
    // 封，角色不可使用仙术和物品
    SealMagic = 2,
    // 禁，角色不可使用物品和特技，不可使用逃跑
    BanProp = 3,
    // 眠，角色处于不可操作状态，受攻击可解除
    Sleep = 4,
    // 狂，角色无法控制，不分敌我的进行普通攻击，攻击力加倍
    Crazy = 5,
    // 乱，角色无法控制，不分敌我，可做战斗中除了使用物品以外的任意事情
    Chaos = 6
};

enum class PAL4_API ECombatStatus
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
