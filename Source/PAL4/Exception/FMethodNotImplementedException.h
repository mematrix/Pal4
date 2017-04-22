#pragma once

#include <string>


class FMethodNotImplementedException : public std::exception
{
public:
    explicit FMethodNotImplementedException(const std::string& msg) noexcept :
        Message(msg)
    {
    }

    explicit FMethodNotImplementedException(const char* msg) noexcept :
        Message(msg)
    {
    }

    char const* what() const noexcept override
    {
        return Message.c_str();
    }

private:
    std::string Message;
};
