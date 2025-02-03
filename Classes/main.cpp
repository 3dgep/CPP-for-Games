#include <iostream>

struct Entity
{
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

Entity::Entity(int hitPoints)
    : hitPoints(hitPoints)
{ 
    std::cout << "Entity::Entity(" << this->hitPoints << ")" << std::endl;
}

Entity::Entity(const Entity& e)
    : hitPoints(e.hitPoints)
{
    std::cout << "Entity::Entity(const Entity& e)" << std::endl;
}

Entity::~Entity()
{
    std::cout << "Entity::~Entity()" << hitPoints << std::endl;
}

void Entity::draw() const
{
    std::cout << "Entity::draw()" << std::endl;
}

struct Player : Entity
{
    explicit Player(int hitPoints = 100);
    ~Player();

    void draw() const override;
    void update(float deltaTime) override;

private:
    int score = 0;
};

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