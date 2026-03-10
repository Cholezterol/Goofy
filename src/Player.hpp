#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    bool locked = false;
    int gold = 0;
    int health = 100;
    int m_keyCount = 0;
    int m_leverCount = 0;
    int damage = 9;
    int strength = 10;
    int block = 5;
private:
};