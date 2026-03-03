#include "Riddler.hpp"
#include "Room.hpp"
#include "fogpi/io.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
void Riddler::Start(Vec2 _pos) {
    m_character = 'R';
    m_position = _pos;
    Riddle chosen;

    std::ifstream riddleFile("assets/Riddles.txt");
    if (!riddleFile)
    {
        std::cerr << "Error opening riddles file!" << std::endl;
        return;
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
    std::cout << "\nAnswer: " << chosen.question << "\n";
}

void Riddler::Update() {
    //while(request_char("hit w to continue: ") != 'w') {}

}