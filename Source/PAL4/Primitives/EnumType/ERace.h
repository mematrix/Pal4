#pragma once

// 此处不使用Demon作为妖的枚举id，因为在仙剑世界观中妖并不就是恶，更何况我们的主角梦璃元身就是一只妖:)
// 以Immortal和God作为仙和神的名称，不一定符合仙剑四设定，也未必符合中国道家的定义（仙是修行境界，
// 神是他人封的，不同于西方上帝神），但毕竟汉语文化和英语文化本就不同，将就用着吧- -
enum class PAL4_API ERace : unsigned char
{
    // 人
    Human = 0,
    // 妖
    Yao,
    // 仙
    Immortal,
    // 鬼
    Ghost,
    // 神
    God,
    // 灵
    Soul,
    // 兽
    Animal
};
