#pragma once
#include <string>
#include <fstream>
#include "Room.hpp"
class Obj
{
public:
    Vec2 pos;
    bool interacted;
    std::string action;
    Room* room = nullptr;
    void dostuff();
    void Start(Vec2 _pos);
private:   
    bool used;
    void leverslot();
    void potionheal();
};   
