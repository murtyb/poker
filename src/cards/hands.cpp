#include "..\..\include\cards\hands.h"


Hand::Hand(const std::vector<Card>& cards)
    : m_cards(cards)
{
    m_is_pocket_pair = hand_is_pocket_pair();
    set_high_and_low_card_values();
}        

bool Hand::hand_is_pocket_pair()
{
    return (m_cards[1].get_value() == m_cards[2].get_value());
}

void Hand::set_high_and_low_card_values()
{
    int card_1_value = m_cards[1].get_value();
    int card_2_value = m_cards[2].get_value();
    if (card_1_value > card_2_value)
    {
        m_high_card_value = card_1_value;
        m_low_card_value = card_2_value;
    }
    else
    {
        m_high_card_value = card_2_value;
        m_low_card_value = card_1_value;
    }
}

bool Hand::operator==(const Hand& hand) const
{
    for (int i = 0; i <m_cards.size(); i++)
    {
        if (m_cards[i].get_value() != hand.m_cards[i].get_value()) {return false;}
    }
    return true;
}

bool Hand::get_is_pocket_pair() const
{
    return m_is_pocket_pair;        
}

int Hand::get_high_card_value() const
{
    return m_high_card_value;        
}

int Hand::get_low_card_value() const
{
    return m_low_card_value;        
}

int Hand::size() const
{
    return m_cards.size();
}

Card Hand::get_card(const int& x) const
{
    return m_cards[x];
}

std::string Hand::get_symbols()
{
    std::string symbols = "";
    for (Card card: m_cards)
    {
        symbols += card.get_symbol();
    }
    return symbols;
}

std::ostream& operator<<(std::ostream& stream, const Hand& hand)
{
    for (Card card: hand.m_cards)
    {
        stream << card;
    }
    return stream;
}

