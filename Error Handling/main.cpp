#include "final_action.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <expected>
#include <system_error>

class Document {
public:
    Document() = default;

    Document(std::string contents)
        : contents{ std::move(contents) }
    {
    }

    bool isEmpty() const
    {
        return contents.empty();
    }

    const std::string& getContent() const {
        return contents;
    }

    void setContents(std::string newContents) {
        contents = std::move(newContents);
    }

    Document& operator<<(const std::string& text) {
        contents += text;
        return *this;
    }

private:
    std::string contents;  // Placeholder for document content
};

namespace
{
    std::ostream& operator<<(std::ostream& os, const Document& doc) {
        // Example content for demonstration purposes
        os << doc.getContent();
        return os;
    }

    bool saveDocument(const std::string& filename, const Document& doc) {

        if (doc.isEmpty())
        {
            return false;  // Cannot save empty document
        }

        std::ofstream file(filename);

        if (!file) {
            return false;  // Failed to open file
        }

        // Write document content
        if (!(file << doc)) {
            return false;  // Failed to write content
        }

        return true;  // Success
    }

    enum class ReturnCode : uint8_t {
        SUCCESS,
        ERROR_OPENING_FILE,
        ERROR_READING_FILE,
        ERROR_EMPTY_FILE,
        ERROR_VALIDATING_DOCUMENT,
        ERROR_PROCESSING_CONTENT,
        ERROR_CLOSING_DOCUMENT,
        ERROR_INVALID_ID,
        ERROR_DATABASE,
    };


    ReturnCode openDocument(const std::string& filename, Document& doc) {
        std::ifstream file(filename);

        if (!file) {
            return ReturnCode::ERROR_OPENING_FILE;  // Failed to open file
        }

        std::ostringstream oss;
        oss << file.rdbuf();

        if (oss.bad())
        {
            return ReturnCode::ERROR_READING_FILE;  // Failed to read content
        }

        std::string contents = oss.str();

        if (contents.empty())
        {
            return ReturnCode::ERROR_EMPTY_FILE; // File is empty
        }

        doc << contents;

        return ReturnCode::SUCCESS;
    }

    ReturnCode validateDocument(const Document& doc) {
        if (doc.isEmpty()) {
            return ReturnCode::ERROR_VALIDATING_DOCUMENT;  // Document is empty
        }
        // Simulate validation logic
        return ReturnCode::SUCCESS;
    }

    ReturnCode processContent(const Document& doc)
    {
        if (doc.isEmpty()) {
            return ReturnCode::ERROR_PROCESSING_CONTENT;  // Cannot process empty document
        }
        // Simulate processing content
        std::cout << "Processing document content: " << doc << std::endl;
        return ReturnCode::SUCCESS;  // Processing successful
    }

    ReturnCode closeDocument(const std::string& fileName, Document& doc) {
        if (!saveDocument(fileName, doc))
        {
            return ReturnCode::ERROR_CLOSING_DOCUMENT;  // Failed to save document
        }
        return ReturnCode::SUCCESS;  // Document closed successfully
    }

    ReturnCode processDocument(const std::string& filename) {
        Document doc;
        ReturnCode result = openDocument(filename, doc);
        if (result != ReturnCode::SUCCESS) {
            closeDocument(filename, doc);
            return result;  // Propagate error
        }

        result = validateDocument(doc);
        if (result != ReturnCode::SUCCESS) {
            closeDocument(filename, doc);  // Cleanup
            return result;    // Propagate error
        }

        result = processContent(doc);
        if (result != ReturnCode::SUCCESS) {
            closeDocument(filename, doc);  // Cleanup
            return result;    // Propagate error
        }

        // Return result of closing
        return closeDocument(filename, doc);
    }

    // Modern C++23 version:
    std::expected<Document, ReturnCode> openDocumentExpected(const std::string& filename) {
        std::ifstream file(filename);

        if (!file) {
            return std::unexpected(ReturnCode::ERROR_OPENING_FILE);  // Failed to open file
        }

        std::ostringstream oss;
        oss << file.rdbuf();

        if (oss.bad()) {
            return std::unexpected(ReturnCode::ERROR_READING_FILE);  // Failed to read content
        }

        std::string contents = oss.str();

        if (contents.empty()) {
            return std::unexpected(ReturnCode::ERROR_EMPTY_FILE); // File is empty
        }

        return Document{ contents };
    }

    void demonstrateErrno() {
#pragma warning(push)
#pragma warning(disable : 4996) // Disable deprecated function warnings (e.g., for fopen)
        FILE* file = fopen("nonexistent_file.txt", "r");
        if (file == nullptr) {
            std::cout << "Error opening file: " << std::strerror(errno) << std::endl;
        }
        else {
            fclose(file);
        }
#pragma warning(pop)
    }

    void createDirectory(const std::string& dir)
    {
        std::error_code ec; // Use a local error code.
        std::filesystem::create_directory(dir, ec);

        if (ec)
        {
            std::cout << "Error:    " << ec.message() << std::endl;
            std::cout << "Category: " << ec.category().name() << std::endl;
            std::cout << "Value:    " << ec.value() << std::endl;
        }
    }

    bool parseInteger(const std::string& input,
        int& result, std::string& errorMsg) {
        try {
            result = std::stoi(input);
            return true;
        }
        catch (const std::exception& e) {
            errorMsg = e.what();
            return false;
        }
    }

    class UserData
    {
    public:
        UserData() = default;

        explicit operator bool() const noexcept { return id > 0 && !name.empty(); }
    private:
        int id = 0;
        std::string name;
    };

    ReturnCode getUserData(int userId, UserData* data) {
        if (userId <= 0) {
            return ReturnCode::ERROR_INVALID_ID;
        }

        // Retrieve user data
        UserData retrievedData{}; // Simulate retrieving user data from a database.
        if (!retrievedData /* database error */) {
            return ReturnCode::ERROR_DATABASE;
        }

        // Populate data structure
        *data = retrievedData;
        return ReturnCode::SUCCESS;
    }

    using ErrorCallback = void (*)(int errorCode, const char* message);

    void processFile(const char* filename, ErrorCallback onError = nullptr) {
#pragma warning(push)
#pragma warning(disable : 4996) // Disable deprecated function warnings (e.g., for fopen)
        FILE* file = fopen(filename, "r");
        if (!file) {
            if (onError) {
                onError(errno, std::strerror(errno));
            }
            return;
        }

        // Process file...
        fclose(file);
#pragma warning(pop)
    }

    // Usage
    void handleError(int code, const char* msg) {
        std::cerr << "Error " << code << ": " << msg << std::endl;
    }
}

int main()
{
    // 1. Return codes and Error flags
    {
        Document doc("The quick brown fox jumps over the lazy dog.\n");

        // Boolean flag for error handling
        if (saveDocument("document.txt", doc))
        {
            std::cout << "Document saved successfully." << std::endl;
        }
        else
        {
            std::cerr << "Error: Failed to save document." << std::endl;
        }

        // Enum is more expressive about the error.
        ReturnCode result = processDocument("document.txt");

        if (result == ReturnCode::ERROR_OPENING_FILE)
        {
            std::cerr << "Error: Could not open the document file." << std::endl;
        }
        else if (result == ReturnCode::ERROR_READING_FILE)
        {
            std::cerr << "Error: Could not read the document file." << std::endl;
        }
        else if (result == ReturnCode::ERROR_VALIDATING_DOCUMENT)
        {
            std::cerr << "Error: Document validation failed." << std::endl;
        }
        else if (result == ReturnCode::ERROR_PROCESSING_CONTENT)
        {
            std::cerr << "Error: Could not process the document content." << std::endl;
        }
        else if (result == ReturnCode::ERROR_CLOSING_DOCUMENT)
        {
            std::cerr << "Error: Could not close the document properly." << std::endl;
        }
        else // It must have succeeded??
        {
            std::cout << "Document processed successfully." << std::endl;
        }

        // Modern C++23 version using std::expected
        if (auto expectedDoc = openDocumentExpected("document.txt"))
        {
            std::cout << "Document processed successfully with expected: " << expectedDoc.value() << std::endl;
        }
        else
        {
            switch (expectedDoc.error())  // NOLINT(clang-diagnostic-switch-enum)
            {
            case ReturnCode::ERROR_OPENING_FILE:
                std::cerr << "Error: Could not open the document file." << std::endl;
                break;
            case ReturnCode::ERROR_READING_FILE:
                std::cerr << "Error: Could not read the document file." << std::endl;
                break;
            case ReturnCode::ERROR_VALIDATING_DOCUMENT:
                std::cerr << "Error: Document validation failed." << std::endl;
                break;
            case ReturnCode::ERROR_PROCESSING_CONTENT:
                std::cerr << "Error: Could not process the document content." << std::endl;
                break;
            case ReturnCode::ERROR_CLOSING_DOCUMENT:
                std::cerr << "Error: Could not close the document properly." << std::endl;
                break;
            default:
                std::cerr << "Unknown error occurred." << std::endl;
            }
        }
    }

    // 2. Global error state
    {
        // This should fail since I don't have a z: drive.
        createDirectory("Z:\\temp");
    }

    // 3. Output parameters
    {
        for (const auto str : { "123", "42", "-42", "3.14","21474836478", "one" })
        {
            int value;
            std::string error;
            if (parseInteger(str, value, error)) {
                std::cout << "Value: " << value << std::endl;
            }
            else {
                // Handle error
                std::cerr << "Parse error: " << error << std::endl;
            }
        }
    }

    // 4. Error callback functions.
    {
        // in main.cpp...
        processFile("document.doc", handleError);
    }

    return 0;
}