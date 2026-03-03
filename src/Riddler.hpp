#pragma once

#include "Entity.hpp"
#include <string>
#include <fstream>
class Riddler : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
private:
    struct Riddle {
    std::string question;
    std::string answer;
    std::string hint1;
    std::string hint2;
    std::string hint3;
    };
};