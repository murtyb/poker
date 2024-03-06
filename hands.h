#pragma once

#include <string>
#include <vector>
#include "cards.h"

class Hand
{
public:
    Hand() = default;
    Hand(const Card& card_1, const Card& card_2);

    bool operator<=(const Hand& hand) const;
    bool operator==(const Hand& hand) const;
    bool get_is_pocket_pair() const;
    int get_high_card_value() const;
    int get_low_card_value() const;
    Card get_card(const int& x) const;
    friend std::ostream& operator<<(std::ostream& stream, const Hand& hand);

private:
    Card m_card_1;
    Card m_card_2;
    int m_high_card_value;
    int m_low_card_value;
    bool m_is_pocket_pair;

    bool hand_is_pocket_pair();
    void set_high_and_low_card_values();
};
