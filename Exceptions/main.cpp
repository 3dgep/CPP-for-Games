#include <complex>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <ios> // for std::ios_base::failure
#include <vector>
#include <format>
#include <print>

namespace
{
    enum class Result : uint8_t
    {
        SUCCESS,
        ERROR_DIVIDE_BY_ZERO
    };

    class MyException : public std::exception
    {
    public:
        MyException() noexcept
            : std::exception("MyException")
        {
        }

        MyException(const char* const message) noexcept
            : std::exception(message)
        {
        }

        ~MyException() noexcept override = default;
    };

    // Traditional error handling technique.
    Result divide(int numerator, int denominator, int* result)
    {
        if (denominator == 0)
        {
            return Result::ERROR_DIVIDE_BY_ZERO;
        }

        if (result)
            *result = numerator / denominator;

        return Result::SUCCESS;
    }

    // Using exceptions
    int divide(int numerator, int denominator)
    {
        if (denominator == 0)
            throw std::invalid_argument("Division by zero");

        return numerator / denominator;
    }

    void processFile(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if (!file)
        {
            throw std::ios_base::failure("Failed to open file: " + fileName);
        }

        // Read and process file...
        if (true /* some error condition occured */)
        {
            throw std::runtime_error("Failed to process file: " + fileName);
        }
    }

    void outer()
    {
        try
        {
            processFile("data.txt");
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // When using standard exceptions, select the most appropriate exception type for each error condition.
    // Dynamic exception specification
    // (deprecated in C++11, removed in C++17)
    std::vector<int> getElements(const std::vector<int>& container, size_t index, size_t count) throw(std::out_of_range, std::length_error) {  // NOLINT(modernize-use-noexcept)
        if (index >= container.size()) {
            throw std::out_of_range(std::format("Index out of range: {}", index));
        }
        if (index + count > container.size()) {
            throw std::length_error(std::format("Requested range ({}, {}) exceeds container bounds: {}", index, index + count, container.size()));
        }

        std::vector<int> result;
        // Extract elements.
        auto first = container.begin() + static_cast<int64_t>(index);
        auto last = first + static_cast<int64_t>(count);
        result.insert(result.begin(), first, last);

        return result;
    }
}

int main()
{
    // 1. Traditional error handling.
    {
        int result;
        int numerator = 1;
        int denominator = 0;
        Result status = divide(numerator, denominator, &result);

        if (status == Result::ERROR_DIVIDE_BY_ZERO)
        {
            std::cerr << "ERROR: Division by zero." << std::endl;
        }
        else
        {
            std::cout << numerator << " / " << denominator << " = " << result << std::endl;
        }
    }

    // 2. Basic exception syntax and semantics.
    try // Wrap code that might throw an exception in a try-catch block.
    {
        int numerator = 1;
        int denominator = 0;
        int result = divide(numerator, denominator);

        std::cout << numerator << " / " << denominator << " = " << result << std::endl;
    }
    // Catch exceptions by (const) reference to avoid object slicing.
    catch (const std::invalid_argument& e) // Catch a specific exception type.
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::exception& e) // Catch a generic exception type.
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    catch (...) // Catch anything else...
    {
        std::cerr << "An unknown exception occurred." << std::endl;
    }

    // 4. Using standard exceptions.
    {
        std::vector vals = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::tuple<size_t, size_t> args[] = { {5, 5}, {5, 10}, {10, 5} };
        for (auto& [index, count] : args)
        {
            try
            {
                // Code that might throw...
                auto res = getElements(vals, index, count);
                std::println("vals: {}", vals);
                std::println("vals[{},{}]: {}", index, index + count, res);
            }
            catch (const std::out_of_range& e)
            {
                // Catch exceptions by (const) reference.
                std::cerr << e.what() << std::endl;
            }
            catch (const std::length_error& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    return 0;
}