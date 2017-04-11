#pragma once


#define MAKE_DEFAULT_COPY_CTOR_AND_OP(ClassName) \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default;
