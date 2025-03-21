#include <fstream>
#include <iostream>

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

        // Write some high scores to "highscores.txt".
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

    // Part 3. Reading the highscores.
    {
        // Open "highscores.txt" for input.
        std::ifstream highscores("highscores.txt", std::ios::in);
        if (!highscores)
        {
            std::cerr << "ERROR: Could not open \"highscores.txt\" for reading." << std::endl;
            return 1; // An error occurred.
        }

        std::cout << "Highscores: " << std::endl;
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

    return 0; // No errors occured.
}
