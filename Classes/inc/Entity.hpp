#pragma once

class Entity
{
public:
    explicit Entity(int hitPoint = 100); // Parameterized constructor.
    ~Entity();

    Entity(const Entity& e); // Copy constructor.

    virtual void draw() const;  // immutable.
    virtual void update(float deltaTime) = 0; // Pure virtual.

    int getHitPoints() const
    {
        return hitPoints;
    }

private:
    int hitPoints = 0;
};
