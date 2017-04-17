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

    template<typename T>
    struct type_alias
    {
        typedef T type;
    };

    template<typename T, bool = std::is_fundamental<T>::value || std::is_enum<T>::value ||
        std::is_pointer<T>::value || std::is_member_pointer<T>::value || std::is_reference<T>::value>
    struct param
    {
    };

    // fundamental type, enum type, pointer and reference: parameter passed by value
    template<typename T>
    struct param<T, true> : type_alias<T>
    {
    };

    // other type (class type): parameter passed by const reference
    template<typename T>
    struct param<T, false> : type_alias<const T&>
    {
    };
}
