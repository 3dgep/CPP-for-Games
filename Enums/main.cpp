#include <iostream>
#include <cstdint>
#include <type_traits>

enum
{
    Monday,
    Tuesday, 
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

int day = Monday;

enum class Color : uint32_t
{
    Black = 0x000000,
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF,
    White = Red | Green | Blue,
    LightGray,
};

Color red = Color::Red;

// uint32_t green = Color::Green;
// Color blue = 2;

auto green = static_cast<std::underlying_type_t<Color>>(Color::Green);

enum class GameState
{
    MainMenu,
    Game,
    GameOver,
    HighScores
};

void doMainMenu();
void doGame();

int main()
{
    GameState gameState = GameState::MainMenu;

    //switch (gameState)
    //{
    //case GameState::MainMenu:
    //    doMainMenu();
    //    break;
    //case GameState::Game:
    //    doGame();
    //    break;
    //case GameState::GameOver:
    //    break;
    //case GameState::HighScores:
    //    break;
    //}

    return 0;
}