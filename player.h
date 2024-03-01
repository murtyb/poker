#pragma once

#include "hands.h"


class Player
{
    public:
    Player(const int& starting_stack);
    
    private:
    double stack;
    Hand hand;
};