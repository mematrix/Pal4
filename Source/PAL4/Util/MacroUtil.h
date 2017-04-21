#pragma once


#define MAKE_DEFAULT_COPY_CTOR_AND_OP(ClassName) \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default;

#define MAKE_DEFAULT_COPY_MOVE_CTOR_AND_OP(ClassName) \
    ClassName(const ClassName&) = default; \
    ClassName(ClassName&&) = default; \
    ClassName& operator=(const ClassName&) = default; \
    ClassName& operator=(ClassName&&) = default;
