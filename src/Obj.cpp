#include "Obj.hpp"
#include "Room.hpp"
#include "player.hpp"
#include "fogpi/io.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
void Obj::Start(Vec2 _pos) 
{
    pos = _pos;
    used = false;
}

void Obj::dostuff() 
{
    if (used == true)
    {
        std::cout << "There is nothing to do here. \n";
        return;
    }
    else
    {
        if (action == "LeverSlot") 
        {
            leverslot();
        }
        else if (action == "potionheal") 
        {
            potionheal();
        }
    }

}

void Obj::leverslot() 
{
    if (room->m_player->m_leverCount > 0)
    {
        std::cout << "You Insert the lever. \n";
        used = true;
    }
    else
    {
        std::cout << "There is a lever slot here, but you don't have a lever! \n";
    }
}


void Obj::potionheal() 
{
    if (room->m_player->health < 100)
    {
        std::cout << "You use the potion and feel better. \n";
        if (room->m_player->health + 60 > 100)
        {
            room->m_player->health = 100;
        }
        else
        {
            room->m_player->health += 60;
        }
        std::cout << "Health is now " << room->m_player->health << " \n";
        used = true;
    }
    else
    {
                std::cout << "You can't use the potion right now. \n";
    }
}
