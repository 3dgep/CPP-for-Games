#include "final_action.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <expected>

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
        if ( !(file << doc)) {
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
        ERROR_CLOSING_DOCUMENT
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
    std::expected<Document, ReturnCode> processDocumentExpected(const std::string& filename) {
        Document doc;
        // Use a final_action to ensure the document is closed properly
        // regardless of the outcome of the operations.
        auto _ = finally([&]
        {
            closeDocument(filename, doc);
        });

        ReturnCode result = openDocument(filename, doc);
        if (result != ReturnCode::SUCCESS) {
            return std::unexpected(result);  // Propagate error.
        }

        result = validateDocument(doc);
        if (result != ReturnCode::SUCCESS) {
            return std::unexpected(result);    // Propagate error.
        }

        result = processContent(doc);
        if (result != ReturnCode::SUCCESS) {
            return std::unexpected(result);    // Propagate error.
        }

        return doc;
    }

void demonstrateErrno() {
    FILE* file = fopen("nonexistent_file.txt", "r");
    if (file == nullptr) {
        std::cout << "Error opening file: " << std::strerror(errno) << std::endl;
    }
    else {
        fclose(file);
    }
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
        if (auto expectedDoc = processDocumentExpected("document.txt"))
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

    return 0;
}