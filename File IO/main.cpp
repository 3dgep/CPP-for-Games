#include <fstream>
#include <iostream>

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

        // Close the file!
        highscores.close();

        // The highscores file is automatically closed when it goes out of scope.
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

        // The highscores file is automatically closed when it goes out of scope.
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
        }

        // Close the file!
        highscores.close();
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

        std::cout << "High Scores (ASCII):  " << std::endl;
        std::string name;
        int score;
        while (highscores >> name >> score)
        {
            std::cout << name << " " << score << std::endl;
        }

        if (highscores.bad())
        {
            std::cerr << "ERROR: An error occured while reading the file." << std::endl;
            return 1; // An error occurred.
        }

        // Close the file!
        highscores.close();

        // The highscores files is automatically closed when it goes out of scope.
    }

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

        // Close the file!
        highscores.close();

        // The file will be automatically closed when it goes out of scope.
    }

    return 0; // No errors occured.
}
