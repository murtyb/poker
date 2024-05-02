#include "..\..\include\game_logic\pot.h"
#include "pot.h"

Pot::Pot(std::vector<PokerPlayer*> possible_winners)
    : m_possible_winners(possible_winners), 
      m_contribution(calculate_contribution())
{
    gather_chips();
}

Chips Pot::calculate_contribution()
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
    Chips ammount_due = m_pot_total/num_of_winners;
    for(PokerPlayer* winner: winners)
    {
        m_pot_total -= ammount_due;
        winner->m_stack += ammount_due;
    }
    allocate_remaining_chips(winners);
}

void Pot::allocate_remaining_chips(std::vector<PokerPlayer*>& winners)
{
    int recipient_position = 0;
    while(Chips(1, 'c') <= m_pot_total)
    {
        m_pot_total -= Chips(1, 'c');
        winners[recipient_position]->m_stack += Chips(1, 'c');
        recipient_position = (recipient_position + 1) % winners.size();
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

std::vector<PokerPlayer*> Pot::find_winners(std::vector<PokerPlayer*>& non_folded_players, const WinRules& win_rules)
{
    return win_rules.find_winners(non_folded_players);
}

void Pot::find_and_pay_winners_of_pot(const WinRules& win_rules)
{
    std::vector<PokerPlayer*> non_folded_players = find_non_folded_players();
    std::vector<PokerPlayer*> winners = find_winners(non_folded_players, win_rules);
    divide_up_chips(winners);
}

PotArray::PotArray(PokerPlayerGroup& players)
{
    create_side_pots(players.ordered_by_bet());
}

void PotArray::create_side_pots(std::vector<PokerPlayer*> players)
{
    m_side_pots.push_back(Pot(players));
    if (players.size() > 1)
    {
        players.pop_back();
        create_side_pots(players);
    }
}

void PotArray::find_and_pay_winners(const WinRules& win_rules)
{
    for (Pot& pot: m_side_pots)
    {
        pot.find_and_pay_winners_of_pot(win_rules);
    } 
}
