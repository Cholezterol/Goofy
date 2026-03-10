#include "Room.hpp"

#include "Player.hpp"
#include "Riddler.hpp"
#include "Skeleton.hpp"
#include "Obj.hpp"
#include <iostream>
#include <fstream>
#include <string>
void Room::Load(std::string _path)
{
    m_map.clear();
    m_doors.clear();
    m_riddlers.clear();
    m_skeletons.clear();
    m_chests.clear();
    m_objects.clear();
    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word)
    {
        if (word == "level")
        {
            if (file >> number)
            {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level")
        {
            std::string levCode;
            std::string path;
            if (file >> levCode >> path)
            {
                Door door;
                door.target = levCode[0] - '0';
                door.locked = levCode[1] == 'L';
                door.path = path;
                m_doors.push_back(door);
            }

        }

        if (word == "Object_info")
        {
            std::string obj_content;
            if (file >> obj_content )
            {
                Obj obj;
                obj.action = obj_content;
                std::cout << "\n object action is " << obj.action << "\n";
                m_objects.push_back(obj);
            }

        }

        if (word == "Chest_Info")
        {
            std::string chestContent;
            if (file>> chestContent)
            {
                Chest chest;
                chest.opened = false;

                if (chestContent == "Lever")
                {
                    chest.content = chestContent;
                    m_chests.push_back(chest);
                }
                else
                {
                    chest.content = "Empty";
                    chest.opened = false;
                    m_chests.push_back(chest);
                }
            }
        }
        if (word == "map")
        {
            m_map.push_back(std::vector<char>());
            while(file >> word)
            {
                if (word == "-2")
                {
                    break;
                }

                if (word == "-1")
                {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
                
            }
        }
    }

    int doorCount = 0;
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == 'B')
            {
                if (m_player == nullptr)
                    m_player = new Player();
                
                m_player->Start(Vec2(x,y));
                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == 'R')
            {
                Riddler r;
                r.Start(Vec2(x,y));
                m_riddlers.push_back(r);
                m_map[y][x] = 'R';
            }

            if (m_map[y][x] == 'S')
            {
                Skeleton s;
                s.Start(Vec2(x,y));
                m_skeletons.push_back(s);
                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == '?')
            {
               for (int i = 0; i < m_objects.size(); i++)
                {
                    m_objects[i].pos = Vec2(x,y);
                    break;
                }
            }

            if (m_map[y][x] == 'C')
            {
                for (int i = 0; i < m_chests.size(); i++)
                {
                        m_chests[i].pos = Vec2(x,y);
                        break;
                }
            }

            if (isdigit(m_map[y][x]) && m_map[y][x] != '0')
            {
                int levelNum = m_map[y][x] - '0'; 
                for (int i = 0; i < m_doors.size(); i++)
                {
                    if (m_doors[i].target == levelNum)
                    {
                        m_doors[i].pos = Vec2(x,y);
                        break;
                    }
                }
            }
        }
    }
}

void Room::Update()
{
    if (m_player != nullptr)
    {
        m_player->room = this;
        m_player->Update();
        if (m_player->locked == false) {
                Draw();
        }
    }
}

void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vec2(x, y)));
        }
        printf("\n");
    }
}

char Room::GetLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return ' ';
    
    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();
    for (int i = 0; i < m_skeletons.size(); i++)
    {
        m_skeletons[i].player = m_player;
        if (m_skeletons[i].pos == _pos && m_skeletons[i].alive)
            return m_skeletons[i].Draw();
    }
    
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return;
    
    if (_pos.x >= m_map[_pos.y].size())
        return;
    
    m_map[_pos.y][_pos.x] = ' ';
}

void Room::OpenDoor(Vec2 _pos)
{
    for(int i = 0; i < m_doors.size(); i++)
    {
        if (m_doors[i].pos == _pos)
        {

            if (m_doors[i].locked && m_player->m_keyCount <= 0)
            {
                std::cout << "\n The door is locked! You'll need to find a key! \n";
                return;
            }
            else if (m_doors[i].locked && m_player->m_keyCount > 0)
            {
                 std::cout << "\n Door Unlocked! \n";
                 m_player->m_keyCount--;
            }
            else
            {
                std::cout << "\n You open the door! \n";
            }

            Load(m_doors[i].path.c_str());       
            return;
         }
    }
}

void Room::OpenChest(Vec2 _pos)
{
    for(int i = 0; i < m_chests.size(); i++)
    {
        if (m_chests[i].pos == _pos)
        {
            if (m_chests[i].opened == false)
            {
                if (m_chests[i].content == "Lever")
                {
                    std::cout << "\n You open the chest and find a Lever! \n";
                    m_player->m_leverCount++;
                    m_chests[i].opened = true;
                }
            }
            else
            {
                std::cout << "\n The chest is empty! \n";
            }
            return;
         }
    }
}
void Room::updateSkeletons(Vec2 _pos)
{
    for (int i = 0; i < m_skeletons.size(); i++)
    {
        if (m_skeletons[i].alive == false)
            continue;
        if(m_skeletons[i].stepCloser(m_player->GetPosition()))
        {
            if(m_skeletons[i].DoBattle()) 
            {
                ClearLocation(m_skeletons[i].pos);
                m_player->locked = false;
            }
            else
            {
                std::cout << "\n You have been slain by the skeleton! Game Over! \n";
                std::cout << "Gold:" << m_player->gold << "\n";
                std::getchar();
                exit(0);
            }
        }
    }
}
void Room::DoRiddle(Vec2 _pos)
{
    for(int i = 0; i < m_riddlers.size(); i++)
    {
        if (m_riddlers[i].pos == _pos)
        {
            m_player->locked = true;
            if (m_riddlers[i].Doscene()){
                ClearLocation(_pos);
                m_player->locked = false;
                m_player->gold += 10;
                std::cout << "The Riddler gives you 10 gold and leaves! You now have " << m_player->gold << " gold! \n";
            }
            else{
                m_player->health -= 20;
                m_player->locked = false;
                std::cout << "The Riddler attacks you and you lose 20 health! You now have " << m_player->health << " health! \n";
            }
    
        }
    }
}

void Room::doObject(Vec2 _pos)
{
    for(int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i].pos == _pos)
        {
            m_objects[i].room = this;
            m_objects[i].dostuff();
        }
    }
}