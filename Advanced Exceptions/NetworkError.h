#pragma once
#include "ApplicationError.h"

// Network-related errors
class NetworkError : public ApplicationError {
public:
    explicit NetworkError(const std::string& msg)
        : ApplicationError("Network error: " + msg) {
    }

    std::string getErrorCode() const override {
        return "NET-ERROR";
    }
};

// More specific network errors
class TimeoutError : public NetworkError {
public:
    TimeoutError(const std::string& msg, int timeout)
        : NetworkError{ "Timeout occured: " + msg }
        , timeout{ timeout } {
    }

    std::string getErrorCode() const override {
        return "NET-TIMEOUT-ERROR";
    }

    int getTimeout() const {
        return timeout;
    }

private:
    int timeout;
};