#include "pokerplayergroup.h"
#include <algorithm>

#define TABLE_WIDTH 30

PokerPlayerGroup::PokerPlayerGroup(std::vector<PokerPlayer> players)
    : m_group_members(players),
      m_position_order(pointer_copy()),
      m_table(Table(pointer_copy(), TABLE_WIDTH)),
      m_number_of_players(players.size())
{
}

std::vector<PokerPlayer*> PokerPlayerGroup::pointer_copy()
{
    std::vector<PokerPlayer*> output;
    for (PokerPlayer& element : m_group_members)
    {
        output.push_back(&element);
    }
    return output;
}

void PokerPlayerGroup::move_button()
{
    m_position_order[0]->m_on_button = false;
    std::rotate(m_position_order.begin(), m_position_order.begin() + 1, m_position_order.end());
    m_position_order[0]->m_on_button = true;
    set_positions();
}

void PokerPlayerGroup::set_positions()
{
    int x = 0;
    for (PokerPlayer* p: m_position_order)
    {
        p->m_position = x;
        x++;
    }
    m_action_player = position(m_utg_position);
    m_aggressor = nullptr;
}

void PokerPlayerGroup::eliminate_bankrupt_players()
{
    for (int i = 0; i < m_position_order.size(); i++)
    {
        if (m_position_order[i]->m_stack == 0)
        {
            m_position_order.erase(m_position_order.begin() + i);
        }
    }

    for (int i = 0; i < m_group_members.size(); i++)
    {
        if (m_group_members[i].m_stack == 0)
        {
            m_group_members.erase(m_group_members.begin() + i);
        }
    }
    m_table.update_players(pointer_copy());
}

void PokerPlayerGroup::next_player()
{
    m_action_player = position(m_action_player->m_position + 1);
    if (m_aggressor == m_action_player) {return;}
    if (m_action_player->m_folded) {next_player(); return;}
    if (m_action_player->m_is_all_in) {next_player(); return;}   
}

void PokerPlayerGroup::draw_table()
{
    m_table.draw();
}

PokerPlayer* PokerPlayerGroup::position(int pos)
{
    return m_position_order[pos % m_number_of_players];
}

PokerPlayer* PokerPlayerGroup::sb_player()
{
    return position(m_small_blind_position);
}

PokerPlayer* PokerPlayerGroup::bb_player()
{
    return position(m_big_blind_position);
}

PokerPlayer* PokerPlayerGroup::utg_player()
{
    return position(m_utg_position);
}

int PokerPlayerGroup::size()
{
    return m_number_of_players;
}

std::vector<PokerPlayer*> PokerPlayerGroup::ordered_by_bet()
{
    std::vector<PokerPlayer*> players = pointer_copy();
    sort(players.begin(), players.end(), [](PokerPlayer* p1, PokerPlayer* p2) {return PokerPlayer::compare_player_bets(*p1, *p2);});
    std::reverse(players.begin(), players.end());
    return players;   
}