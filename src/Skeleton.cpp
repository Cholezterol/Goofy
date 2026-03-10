#include "Room.hpp"
#include "fogpi/io.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <cmath>
#include "Skeleton.hpp"
#include "Dice.hpp"
void Skeleton::Start(Vec2 _pos)
{
    m_character = 'S';
    m_position = _pos;
    pos = m_position;
}

bool Skeleton::stepCloser(Vec2 playerPos)
{

    if (std::abs(pos.x - playerPos.x) > std::abs(pos.y - playerPos.y))
    {
        if (pos.x < playerPos.x)
        {
            pos.x += 1.0f; 
        }
        else
        {
           pos.x -= 1.0f;
        }
    }
    else
    {
        if (pos.y < playerPos.y)
        {
            pos.y += 1.0f;
        }
        else
        {
            pos.y -= 1.0f;
        }
    }

    if (pos == playerPos)
    {
        return true;
    }

    return false;
}

bool Skeleton::DoBattle()
{
    std::cout << "\n You enter battle with a skeleton! \n";
    while (alive && player->health > 0)
    {
        std::cout << "Type 1 to attack, 2 to block: \n";
        player->locked = true;
        std::string playerInput;
        playerInput = request_char("Enter Action:");
        if (playerInput == "1")
        {
            RollStats result = RollDice({ {6} });
            health -= player->damage * result.total;
            std::cout << "\n You attack the skeleton and deal " << player->damage * result.total << " damage! The skeleton has " << health << " health left! \n";
            if (health <= 0)
            {
                alive = false;
            }
        } 
        else if (playerInput == "2")
        {
            int blockAmount = player->block;
            std::cout << "\n You block and reduce the skeleton's damage by " << blockAmount << " for this turn! \n";
            damage -= blockAmount;
        }
        else
        {
            std::cout << "\n I said 1 or 2 not your IQ, goofy. \n";
        }

        // Skeleton attacks back :)
        player->health -= damage;
         std::cout << "\n The skeleton attacks you and deals " << damage << " damage! You have " << player->health << " health left! \n";
    }

    if (player->health <= 0)
    {
        std::cout << "\n You have been slain by the skeleton! \n";
        return false;
    }
    else
    {
        std::cout << "\n You have slain the skeleton, He drops 10 gold!\n";
        player->gold += 10;
        std::cout << "You now have " << player->gold << " gold!\n";
        alive = false;
        return true;
    }

}