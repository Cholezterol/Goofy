#pragma once

#include "Entity.hpp"
#include <string>
#include <fstream>

struct Riddle {
std::string question;
std::string answer;
std::string hint1;
std::string hint2;
std::string hint3;
};

class Riddler : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    Vec2 pos;
    Riddle chosen;
    int hintcount = 3;
    bool Doscene();
private:

};