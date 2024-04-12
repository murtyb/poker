#pragma once

#include "cards.h"



class Hand
{
public:
    Hand() = default;
    Hand(const std::vector<Card>& cards);

    bool operator<=(const Hand& hand) const;
    bool operator==(const Hand& hand) const;
    bool get_is_pocket_pair() const;
    int get_high_card_value() const;
    int get_low_card_value() const;
    int size() const;
    Card get_card(const int &x) const;
    friend std::ostream& operator<<(std::ostream& stream, const Hand& hand);
    std::string get_symbols();

private:
    std::vector<Card> m_cards;
    int m_high_card_value;
    int m_low_card_value;
    bool m_is_pocket_pair;

    bool hand_is_pocket_pair();
    void set_high_and_low_card_values();
};
