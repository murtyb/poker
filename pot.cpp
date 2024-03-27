#include "Pot.h"

Pot::Pot(std::vector<Player*>& possible_winners)
    : m_possible_winners(possible_winners), 
      m_contribution_cap(calculate_cap()), 
      m_pot_total(0)
{
    gather_chips();
}

double Pot::calculate_cap()
{
    Player* player_with_smallest_bet = m_possible_winners.back();
    return  player_with_smallest_bet->m_ammount_bet;
}

void Pot::gather_chips()
{
    for (Player* player: m_possible_winners)
    {
        if(player->m_ammount_bet <= m_contribution_cap)
        {
            player->m_ammount_bet = 0;
            m_pot_total += player->m_ammount_bet;
        }
        else
        {
            player->m_ammount_bet -= m_contribution_cap;
            m_pot_total += m_contribution_cap;
        } 
    }
}

void Pot::divide_up_chips(std::vector<Player*>& winners)
{
    int num_of_winners = winners.size();
    double ammount_due = m_pot_total/num_of_winners;
    for(Player* winner: winners)
    {
        winner->m_stack += ammount_due;
    }
}

std::vector<Player*> Pot::find_non_folded_players()
{
    std::vector<Player*> non_folded_players;
    for (Player* player: m_possible_winners)
    {
        if (!player->m_folded) {non_folded_players.push_back(player);}
    }
    return non_folded_players;
}

Hand Pot::find_winning_hand(std::vector<Player*>& non_folded_players)
{
    sort(non_folded_players.begin(), non_folded_players.end(), Player::compare_player_hands);
    return non_folded_players.back()->m_hand;
}

std::vector<Player*> Pot::find_winners(std::vector<Player*>& non_folded_players)
{
    std::vector<Player*> winning_players;
    Hand winning_hand = find_winning_hand(non_folded_players);
    for (Player* player: non_folded_players)
    {
        if (player->m_hand == winning_hand) {winning_players.push_back(player);}
    }
    return winning_players;
}

void Pot::find_and_pay_winners_of_pot()
{
    std::vector<Player*> non_folded_players = find_non_folded_players();
    std::vector<Player*> winners = find_winners(non_folded_players);
    divide_up_chips(winners);
}

PotArray::PotArray(std::vector<Player*> players)
{
    order_players_by_decreasing_stack(players);
    create_side_pots(players);
}

void PotArray::create_side_pots(std::vector<Player*>& players)
{
    m_side_pots.push_back(Pot(players));
    if (players.size() > 1)
    {
        players.pop_back();
        create_side_pots(players);
    }
}

void PotArray::order_players_by_decreasing_stack(std::vector<Player*>& players)
{
    sort(players.begin(), players.end(), Player::compare_player_stacks);
    std::reverse(players.begin(), players.end());
}

void PotArray::find_and_pay_winners()
{
    for (Pot& pot: m_side_pots)
    {
        pot.find_and_pay_winners_of_pot();
    } 
}
