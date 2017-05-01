#pragma once

// AI类型。用于标识人物在战斗时动作偏向，比如恢复、攻击、仙术、技能等
enum class PAL4_API EAIType
{
    // 主角型
    Protagonist = 0,
    // 普通型
    Common,
    // 好战型
    Bellicose,
    // 逃跑型
    RunAway,
    // 恢复型
    Restorative,
    // Boss型
    Boss,
    // 符灵
    FuLing,
    // 钟魁巨汉
    ZhongKui,
    // 刘安怨魂
    LiuAn,
    // 财神
    CaiShen,
    // 狐三太爷
    HuSanTaiYe,
    // 熔岩兽王
    RongYanShouWang,
    // 句芒
    GouMang,
    // 玄霄
    XuanXiao,
    // 玄霄-变身
    XuanXiaoShift,
    // 狐三太爷1
    HuSanTaiYe1,
    // 赤链蛇
    ChiLianShe,
    // 其它法术
    OtherMagic,
    // 恢复法术
    RestoreMagic,
    // 第几回合
    InSpecialRound,
    // 每隔几回合
    EveryNRound,
    // 魁召甲1
    KuiZhao1,
    // 魁召甲2
    KuiZhao2,
    // 夙瑶
    SuYao
};
