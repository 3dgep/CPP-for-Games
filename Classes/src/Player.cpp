#include <Player.hpp>

#include <iostream>

Player::Player(int hitPoints)
    : Entity(hitPoints)
{
    std::cout << "Player::Player( " << hitPoints << ")" << std::endl;
}

Player::~Player()
{
    std::cout << "Player::~Player()" << std::endl;
}

void Player::draw() const
{
    std::cout << "Player::draw()" << std::endl;
}

void Player::update(float deltaTime)
{
    score += 10;
    std::cout << "Player::update( " << deltaTime << ")" << std::endl;
}
