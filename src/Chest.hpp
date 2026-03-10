#pragma once
#include <string>
#include "fogpi/Math.hpp"

struct Chest
{
    Vec2 pos;
    std::string content;
    bool opened;
};