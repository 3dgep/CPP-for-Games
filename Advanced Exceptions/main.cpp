#include "DatabaseError.h"
#include "NetworkError.h"

#include <expected>
#include <iostream>
#include <format>

namespace
{
    template<typename... Args>
    void logError(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cerr << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }

    void logNestedException(const std::exception& e, int level = 0)
    {
        // Log the (nested) exception.
        logError("{:{}}Exception: {}", "", level * 4, e.what());
        try
        {
            // Rethrow if the original exception is a nested exception.
            // std::rethrow_if_nested(e); // This will call std::terminate if e is of type nested_exception, but there is no nested exception to throw!

            // Rethrow the exception if it is a nested exception (with an actual exception to rethrow).
            // Otherwise, do nothing.
            // This is used to "unroll" the nested exceptions.
            const std::nested_exception* ne = dynamic_cast<const std::nested_exception*>(&e);
            if (ne && ne->nested_ptr())
                ne->rethrow_nested();
        }
        catch (const std::exception& nestedException)
        {
            // Call recursively until there are no more nested exceptions.
            logNestedException(nestedException, level + 1);
        }
    }

    void logIntoServer(std::string_view url)
    {
        // Try to log into the server.
        // But the server didn't respond in a reasonable amount of time.
        throw TimeoutError(std::format("Could not connect to server: {}", url), 100);
    }

    // Function-try blocks.
    std::expected<double, std::string> divide(int numerator, int denominator)
        try
    {
        if (denominator == 0)
            throw std::invalid_argument("Division by zero");

        return numerator / static_cast<double>(denominator);
    }
    catch (const std::exception& e)
    {
        // Can be used to convert exceptions to other types
        return std::unexpected(e.what());
    }
}

class Ratio
{
public:
    // Function try block on constructors will catch
    // exceptions thrown in the constructor initializer list
    // and in the function body.
    Ratio(int numerator, int denominator) try
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
        if (denominator == 0)
            throw std::invalid_argument("Division by zero.");

        m_ratio = numerator / static_cast<double>(denominator);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to construct Ratio: " << e.what() << std::endl;
        // Exception is automatically rethrown.
    }

    // Constructors that could throw an exception should be marked
    // "noexecpt(false)" when used with a destructor try block.
    ~Ratio() noexcept(false) try {
        // A destructor that throws exceptions must be noexcept(false)
        // otherwise the application will terminate.
        throw std::runtime_error("Failed to cleanup class...");
    }
    catch (const std::exception& e) {
        // The best you can hope for is logging of the error...
        std::cerr << "Failed to destruct Ratio: " << e.what() << std::endl;
    }

private:
    int m_numerator = 0;
    int m_denominator = 0;
    double m_ratio = 0.0;
};


int main()
{
    // 1. Custom exception hierarchies
    try
    {
        // Code that might throw various exceptions.
    }
    catch (const QueryError& e) {
        // Handle specific query errors.
        logError("SQL error in query: {}, {}", e.getQuery(), e.what());
    }
    catch (const DatabaseError& e) {
        // Handle any database error not caught above.
        logError("Database error: {}", e.what());
    }
    catch (const TimeoutError& e) {
        // Handle timeout errors.
        logError("Timeout error: ({}ms) {}", e.getTimeout(), e.what());
    }
    catch (const NetworkError& e) {
        // Handle any other network errors.
        logError("Network error: {}", e.what());
    }
    catch (const ApplicationError& e) {
        // Handle any application errors not caught above.
        logError("Application error: {}: {}", e.getErrorCode(), e.what());
    }
    catch (const std::exception& e) {
        // Handle standard library exceptions.
        logError("Standard exception: {}", e.what());
    }
    catch (...) {
        // Handle any other exceptions.
        logError("Unknown exception");
    }

    // 2. Nested exceptions.
    try
    {
        // When we throw a specific exception type...
        logIntoServer("http://localhost:3000");
    }
    catch (...) // We lose the original exception information!
    {
        try
        {
            // And catch it by its base type or using "..."
            // we will lose the original exception information.
            // We can rethrow the exception and wrap it in a nested exception
            // (or derived from nested_exception) to preserve the original exception.
            // Captures the original exception!
            std::throw_with_nested(ApplicationError("..."));
        }
        catch (const std::exception& nestedException)
        {
            logNestedException(nestedException);
        }
    }

    // 3. Function-try blocks.
    {
        try
        {
            int numerator = 1;
            int denominator = 0;

            if (auto result = divide(numerator, denominator))
            {
                std::cout << "The result is" << *result;
            }
            else
            {
                std::cerr << "An error occured: " << result.error() << std::endl;
            }

            Ratio ratio(numerator, denominator);
        }
        catch (const std::exception& e)
        {
            std::cerr << "An error occured. " << e.what() << std::endl;
        }
    }

    return 0;
}