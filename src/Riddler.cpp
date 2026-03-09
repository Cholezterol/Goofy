#include "Riddler.hpp"
#include "Room.hpp"
#include "fogpi/io.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include "Room.hpp"
void Riddler::Start(Vec2 _pos) {
    m_character = 'R';
    m_position = _pos;
    pos = _pos;
}
bool Riddler::Doscene(){
    std::ifstream riddleFile("assets/Riddles.txt");
    if (!riddleFile)
    {
        std::cerr << "Error opening riddles file!" << std::endl;
        return false;
    }
    std::vector<Riddle> riddles;
    while (riddleFile) {
        Riddle r;
        if (!std::getline(riddleFile, r.question)) break;
        if (!std::getline(riddleFile, r.answer)) break;
        if (!std::getline(riddleFile, r.hint1)) break;
        if (!std::getline(riddleFile, r.hint2)) break;
        if (!std::getline(riddleFile, r.hint3)) break;
        riddles.push_back(r);
    }

    int randomIndex = random_int(0, riddles.size() - 1);//1 + rand() % d.sides;
    chosen = riddles[randomIndex];

    std::cout << "\nYou come across a riddler! \n" << chosen.question << "\n";
    while (true) {
        std::string playerInput;
        std::cin >> playerInput;
        std::vector<std::string> hints = { chosen.hint1, chosen.hint2, chosen.hint3 };
        if (playerInput == chosen.answer){
            std::cout << "Correct! You shall pass young travelor! .\n";
            return true;
        }
        else{
            hintcount--;
            if (hintcount > 0){
                std::cout << "Oof, Wrong answer! You have " << hintcount << " hints left! \n Here is your hint:" << hints[4 - hintcount] << "\n";
            }
            else{
                std::cout << "Eek! The Riddler takes offense to your wrong answers and attacks you! \n";
                return false;
            }
        }
    }
}

void Riddler::Update() {

}