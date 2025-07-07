#pragma once

#include "ApplicationError.h"

// Database related errors.
class DatabaseError : public ApplicationError
{
public:
    explicit DatabaseError(const std::string& msg)
        : ApplicationError("Database error: " + msg)
    {}

    std::string getErrorCode() const override
    {
        return "DB-ERROR";
    }
};

// More specific database errors
class ConnectionError : public DatabaseError {
public:
    explicit ConnectionError(const std::string& msg)
        : DatabaseError("Connection failed: " + msg) {
    }

    std::string getErrorCode() const override {
        return "DB-CONNECTION-ERROR";
    }
};

// SQL Query error.
class QueryError : public DatabaseError {
public:
    QueryError(const std::string& msg, std::string sqlQuery)
        : DatabaseError("Query failed: " + msg), query(std::move(sqlQuery)) {
    }

    std::string getErrorCode() const override {
        return "DB-QUERY-ERROR";
    }

    const std::string& getQuery() const {
        return query;
    }

private:
    std::string query;

};