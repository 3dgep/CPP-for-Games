#include <iostream>
#include <string>

class Entity
{
    // Class member variables.
    // Class member functions.
public:
    virtual void update(float deltaTime);
    virtual void draw();

    const std::string& getName() const
    {
        return name;
    }

    void setName(const std::string& _name)
    {
        name = _name;
    }

protected:

private:
    std::string name;
};

void Entity::update(float deltaTime)
{
    std::cout << "Entity::update()" << std::endl;
}

void Entity::draw()
{
    std::cout << "Entity::draw()" << std::endl;
}

class Player : public Entity
{
public:
    explicit Player(int _hitPoints = 100)
        : hitPoints(_hitPoints)
    {}

    void update(float deltaTime) override;
    void draw() override;

    int getHitPoints() const
    {
        return hitPoints;
    }

private:
    int hitPoints = 0;
    int score = 0;
};

void Player::update(float deltaTime)
{
    std::cout << "Player::update()" << std::endl;
}

void Player::draw()
{
    std::cout << "Player::draw()" << std::endl;
}

class Enemy : public Entity
{
public:
    void update(float deltaTime) override;
    void draw() override;

private:
    int hitPoints;
};

void Enemy::update(float deltaTime)
{
    std::cout << "Enemy::update()" << std::endl;
}

void Enemy::draw()
{
    std::cout << "Enemy::draw()" << std::endl;
}

Entity* entities[11]{};

void printHitPoints(const Player& p)
{
    std::cout << "p.hitPoints: " << p.getHitPoints() << std::endl;
}

int main()
{
    entities[0] = new Player(10);
    for (int i = 1; i < 11; ++i)
    {
        entities[i] = new Enemy();
    }

    printHitPoints(Player{100});

    bool isRunning = true;

    while (isRunning)
    {
        for (Entity* e : entities)
        {
            e->update(0.1f);
        }

        for (Entity* e : entities)
        {
            e->draw();
        }

        isRunning = false;
    }


    return 0;
}