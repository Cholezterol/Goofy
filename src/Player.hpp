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
private:
};