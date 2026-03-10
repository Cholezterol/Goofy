#pragma once

#include "Entity.hpp"
#include <string>
#include <fstream>
#include "Player.hpp"

class Skeleton : public Entity
{
    public:
        void Start(Vec2 _pos);
        bool stepCloser(Vec2 playerPos);
        bool DoBattle();
        Vec2 pos;
        int health = 100;
        int damage = 20;
        Player* player = nullptr;
        bool alive = true;
    private:

};