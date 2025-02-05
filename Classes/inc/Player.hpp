#pragma once

#include "Entity.hpp"

class Player: public Entity
{
public:
    explicit Player(int hitPoints = 100);
    ~Player();

    void draw() const override;
    void update(float deltaTime) override;

private:
    int score = 0;
};
