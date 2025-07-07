#pragma once

#include <exception>
#include <string>

// Base class for all application-specific exceptions.
class ApplicationError : public std::exception, public std::nested_exception
{
public:
    explicit ApplicationError(std::string msg)
        : message(std::move(msg))
    {
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    virtual std::string getErrorCode() const
    {
        return "APP-GENERAL-ERROR";
    }

private:
    std::string message;
};
