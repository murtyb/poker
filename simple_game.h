#pragma once

#include "game.h"


class SimpleGame: public Game
{
    SimpleGame(std::vector<Player>& players, Deck deck);
};