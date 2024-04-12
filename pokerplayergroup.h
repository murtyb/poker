#pragma once

#include "pokerplayer.h"
#include "table.h"

class PokerPlayerGroup
{
    public:
    PokerPlayer* m_aggressor = nullptr;
    PokerPlayer* m_action_player = nullptr;

    PokerPlayerGroup(std::vector<PokerPlayer> players);
    PokerPlayer* position(int pos);
    PokerPlayer* utg_player();
    PokerPlayer* sb_player();
    PokerPlayer* bb_player();
    void move_button();
    void eliminate_bankrupt_players();
    void next_player();
    void draw_table();
    int size();
    std::vector<PokerPlayer*> ordered_by_bet(); //in decreasing order

private:
    std::vector<PokerPlayer> m_group_members;
    std::vector<PokerPlayer*> m_position_order;
    int m_number_of_players;
    const int m_small_blind_position = 1;
    const int m_big_blind_position = 2;
    const int m_utg_position = 3;
    Table m_table;
    void set_positions();
    std::vector<PokerPlayer*> pointer_copy();

};