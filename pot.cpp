#include "Pot.h"

Pot::Pot(std::vector<PokerPlayer*> possible_winners)
    : m_possible_winners(possible_winners), 
      m_contribution(calculate_contribution()), 
      m_pot_total(0)
{
    gather_chips();
}

double Pot::calculate_contribution()
{
    PokerPlayer* player_with_smallest_bet = m_possible_winners.back();
    return  player_with_smallest_bet->m_ammount_bet;
}

void Pot::gather_chips()
{
    for (PokerPlayer* player: m_possible_winners)
    {
        player->m_ammount_bet -= m_contribution;
        m_pot_total += m_contribution;
    }
}

void Pot::divide_up_chips(std::vector<PokerPlayer*>& winners)
{
    int num_of_winners = winners.size();
    double ammount_due = m_pot_total/num_of_winners;
    for(PokerPlayer* winner: winners)
    {
        winner->m_stack += ammount_due;
    }
}

std::vector<PokerPlayer*> Pot::find_non_folded_players()
{
    std::vector<PokerPlayer*> non_folded_players;
    for (PokerPlayer* player: m_possible_winners)
    {
        if (!player->m_folded) {non_folded_players.push_back(player);}
    }
    return non_folded_players;
}

Hand Pot::find_winning_hand(std::vector<PokerPlayer*>& non_folded_players)
{
    sort(non_folded_players.begin(), non_folded_players.end(), [](PokerPlayer* p1, PokerPlayer* p2) {return PokerPlayer::compare_player_hands(*p1, *p2);});
    return non_folded_players.back()->m_hand;
}

std::vector<PokerPlayer*> Pot::find_winners(std::vector<PokerPlayer*>& non_folded_players)
{
    std::vector<PokerPlayer*> winning_players;
    Hand winning_hand = find_winning_hand(non_folded_players);
    for (PokerPlayer* player: non_folded_players)
    {
        if (player->m_hand == winning_hand) {winning_players.push_back(player);}
    }
    return winning_players;
}

void Pot::find_and_pay_winners_of_pot()
{
    std::vector<PokerPlayer*> non_folded_players = find_non_folded_players();
    std::vector<PokerPlayer*> winners = find_winners(non_folded_players);
    divide_up_chips(winners);
}

PotArray::PotArray(std::vector<PokerPlayer*> players)
{
    order_players_by_decreasing_bet(players);
    create_side_pots(players);
}

void PotArray::create_side_pots(std::vector<PokerPlayer*>& players)
{
    m_side_pots.push_back(Pot(players));
    if (players.size() > 1)
    {
        players.pop_back();
        create_side_pots(players);
    }
}

void PotArray::order_players_by_decreasing_bet(std::vector<PokerPlayer*>& players)
{
    sort(players.begin(), players.end(), [](PokerPlayer* p1, PokerPlayer* p2) {return PokerPlayer::compare_player_bets(*p1, *p2);});
    std::reverse(players.begin(), players.end());
}

void PotArray::find_and_pay_winners()
{
    for (Pot& pot: m_side_pots)
    {
        pot.find_and_pay_winners_of_pot();
    } 
}
