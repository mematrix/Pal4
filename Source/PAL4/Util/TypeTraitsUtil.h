#pragma once

#include <type_traits>

namespace pal4
{
    template<typename T, T v1, T v2>
    struct is_equal : std::false_type
    {
    };

    template<typename T, T v>
    struct is_equal<T, v, v> : std::true_type
    {
    };
}
