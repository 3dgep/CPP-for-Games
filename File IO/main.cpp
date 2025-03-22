#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

struct highscore
{
    char name[4];
    uint32_t score;
};

int main()
{
    // Part 1. Write some highscores to a file.
    {
        // Open "highscores.txt" for writing. This will create the
        // file if it doesn't exist or truncate the file if it already exists.
        std::ofstream highscores("highscores.txt", std::ios::out);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.txt\" for writing." << std::endl;
            return 1; // An error occurred.
        }

        // Write some highs cores to "highscores.txt".
        highscores << "DAN " << 2014 << std::endl;
        highscores << "TOM " << 2012 << std::endl;
        highscores << "LUC " << 2009 << std::endl;
        highscores << "SUZ " << 1978 << std::endl;

        if (highscores.bad())
        {
            std::cerr << "ERROR: An error occurred while writing." << std::endl;
            return 1; // An error occurred.
        }

        // Close the file!
        highscores.close();

        // Note: The highscores file is automatically closed when it goes out of scope.
    }

    // Part 2. Append some new scores to the file.
    {
        // Open a file for writing, but append new data at the end of the file.
        std::ofstream highscores("highscores.txt", std::ios::out | std::ios::app);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.txt\" for appending." << std::endl;
            return 1; // An error occurred.
        }

        highscores << "JER " << 1977 << std::endl;

        // Close the file!
        highscores.close();

        // Note: The highscores file is automatically closed when it goes out of scope.
    }

    // Part 3. Writing binary data to a file.
    {
        std::ofstream highscores("highscores.bin", std::ios::binary);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.bin\" for writing." << std::endl;
            return 1;
        }

        highscore scores[] = {
            {"DAN", 2014},
            {"TOM", 2012},
            {"LUC", 2009},
            {"SUZ", 1978},
            {"JER", 1977}
        };

        // First write the number of entries:
        unsigned char numScores = std::size(scores);
        highscores.write(reinterpret_cast<const char*>(&numScores), sizeof(numScores));

        // Then write the entries
        highscores.write(reinterpret_cast<const char*>(scores), numScores * sizeof(highscore));

        if (highscores.bad())
        {
            std::cerr << "ERROR: Failed writing data to binary file." << std::endl;
            return 1; // An error occurred.
        }

        // Close the file!
        highscores.close();

        // Note: The highscores file is automatically closed when it goes out of scope.
    }

    // Part 4. Reading the highscores.
    {
        // Open "highscores.txt" for input.
        std::ifstream highscores("highscores.txt", std::ios::in);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.txt\" for reading." << std::endl;
            return 1; // An error occurred.
        }

        std::cout << "High Scores (Text):  " << std::endl;
        std::string name;
        int score;
        while (highscores >> name >> score)
        {
            std::cout << name << " " << score << std::endl;
        }

        if (highscores.bad())
        {
            std::cerr << "ERROR: An error occurred while reading the file." << std::endl;
            return 1; // An error occurred.
        }

        // Close the file!
        highscores.close();

        // Note: The highscores files is automatically closed when it goes out of scope.
    }

    std::cout << std::endl;

    // Part 5. Reading binary data.
    {
        std::ifstream highscores("highscores.bin", std::ios::binary);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.bin\" for reading." << std::endl;
            return 1; // An error occurred.
        }

        // Read the number of records.
        unsigned char numScores;
        highscores.read(reinterpret_cast<char*>(&numScores), sizeof(numScores));

        // Allocate memory to store the highscores.
        highscore* scores = new highscore[numScores];

        // Read the highscores into the allocated memory.
        highscores.read(reinterpret_cast<char*>(scores), numScores * sizeof(highscore));

        if (highscores.bad())
        {
            std::cerr << "ERROR: Failed to read \"highscores.bin\"" << std::endl;
            return 1; // An error occurred.
        }

        // Display the highscore data.
        std::cout << "High Scores (Binary):  " << std::endl;
        for (int i = 0; i < numScores; ++i)
        {
            std::cout << scores[i].name << " " << scores[i].score << std::endl;
        }

        // Delete the scores array to avoid memory leaks.
        delete[] scores;

        // Close the highscores file!
        highscores.close();

        // Note: The file will be automatically closed when it goes out of scope.
    }

    std::cout << std::endl;

    // Part 6. Reading line-by-line.
    {
        std::ifstream highscores("highscores.csv");
        if (!highscores)
        {
            std::cout << "ERROR: Failed to open \"highscores.csv\"" << std::endl;
            return 1; // An error occurred.
        }

        std::cout << "High Scores (CSV):  " << std::endl;

        // Read file line-by-line.
        std::string line;
        bool headerRow = true;
        while (std::getline(highscores, line))
        {
            // Continued...
            if (highscores.bad())
            {
                std::cerr << "ERROR: Failed to read file." << std::endl;
                return 1; // An error occurred.
            }

            if (line.empty()) continue; // Skip empty lines.

            // Skip the header row.
            if (headerRow)
            {
                headerRow = false;
                continue;
            }

            // Print each field of the record.
            {
                std::stringstream ss(line); // From sstream header.
                std::string field;
                // std::getline can take a delimiter to split the row into fields.
                while (std::getline(ss, field, ','))
                {
                    std::cout << field << " ";
                }
            }

            std::cout << std::endl;
        }
    }

    return 0; // No errors occurred.
}
