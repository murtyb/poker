#pragma once

#include <string>
#include <vector>
#include "cards.h"

class Hand
{
public:

    Hand(const Card& card_1, const Card& card_2);

    bool operator<=(const Hand& hand) const;
    bool get_is_pocket_pair() const;
    bool get_high_card_value() const;
    Card get_card(int& x) const;

private:
    Card m_card_1;
    Card m_card_2;
    int m_high_card_value;
    bool m_is_pocket_pair;

    bool hand_is_pocket_pair();
    int highest_card_value();
};

