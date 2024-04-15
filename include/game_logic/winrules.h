#pragma once

#include <algorithm>
#include  "..\players\pokerplayer.h"


class WinRules
{
public:
    virtual std::vector<PokerPlayer*> find_winners(std::vector<PokerPlayer*> players) const = 0;
};

class TwoCardRules: public WinRules
{
public:
    static bool compare_hands(Hand hand_1, Hand hand_2);
    Hand find_winning_hand(std::vector<PokerPlayer*> non_folded_players) const;
    std::vector<PokerPlayer*> find_winners(std::vector<PokerPlayer*> players) const override;
};