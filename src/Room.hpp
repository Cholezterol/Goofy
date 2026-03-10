#pragma once

#include <vector>
#include "Door.hpp"
#include "Riddler.hpp"
#include "Skeleton.hpp"
#include "Chest.hpp"
#include "Obj.hpp"
class Entity;
class Player;
class Monster;
class Skeleton;
class Obj;
class Room {
public:
    void updateSkeletons(Vec2 _pos);
    void Load(std::string _path);
    void Draw();
    void Update();
    char GetLocation(Vec2 _pos);
    void ClearLocation(Vec2 _pos);
    void OpenDoor(Vec2 _pos);
    void DoRiddle(Vec2 _pos);
    void OpenChest(Vec2 _pos);
    void doObject(Vec2 _pos);
    Player* m_player = nullptr;
private:
    std::vector<Entity*> m_entities;
    std::vector<Monster*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
    std::vector<Chest> m_chests;
    std::vector<Riddler> m_riddlers;
    std::vector<Skeleton> m_skeletons;
    std::vector<Obj> m_objects;
};