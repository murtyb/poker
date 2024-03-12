#pragma once

#include <iostream>
#include <utility>
#include "misc.h"
#include "game.h" 
#include <map>


class SimpleGame: public Game
{
    public:
    using Game::Game;
    void get_user_input();
    void request_input_message();
    void print_options();
    void run();
    void play_pre_flop();
    bool in_betting_phase();
    void check_if_limped_to_big_blind();
    void allocate_winnings();
    void end_round();

    bool m_limped_to_big_blind = false;
};
