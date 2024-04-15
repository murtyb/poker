#include "..\..\include\game_logic\winrules.h"


bool TwoCardRules::compare_hands(Hand hand_1, Hand hand_2)
{
    if (hand_1.get_is_pocket_pair() ^ hand_2.get_is_pocket_pair())//If exactly one hand is a pocket pair.
    {
        return hand_2.get_is_pocket_pair();
    }
    else if (hand_1.get_high_card_value() == hand_2.get_high_card_value())
    {
        return hand_1.get_low_card_value() <= hand_2.get_low_card_value();
    }
    else 
    {   
        return hand_1.get_high_card_value() <= hand_2.get_high_card_value();
    }
}

Hand TwoCardRules::find_winning_hand(std::vector<PokerPlayer*> players) const
{
    std::vector<Hand> player_hands;
    for (PokerPlayer* p: players) {player_hands.push_back(p->m_hand);} 
    std::sort(player_hands.begin(), player_hands.end(), compare_hands);
    return player_hands.back();
}

std::vector<PokerPlayer*> TwoCardRules::find_winners(std::vector<PokerPlayer*> players) const
{
    Hand winning_hand = find_winning_hand(players);
    std::vector<PokerPlayer*> winners;
    for (PokerPlayer* player: players)
    {
        if (player->m_hand == winning_hand) {winners.push_back(player);}
    }
    return winners;
}