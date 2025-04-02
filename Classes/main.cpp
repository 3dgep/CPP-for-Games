#include <Player.hpp>

#include <iostream>

union Color
{
    uint32_t rgba;
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
};

void printHitPoints(const Entity& e)
{
    std::cout << "hitPoints: " << e.getHitPoints() << std::endl;
}

int main()
{
    Player player{};

    Entity* e = &player;
    e->update(0.1f);
    e->draw();
    
    return 0;
}