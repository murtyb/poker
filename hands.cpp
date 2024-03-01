#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"


Hand::Hand(const Card& card_1, const Card& card_2)
    : m_card_1(card_1), m_card_2(card_2)
{
    m_is_pocket_pair = hand_is_pocket_pair();
    set_high_and_low_card_values();
}        

bool Hand::hand_is_pocket_pair()
{
    return (m_card_1.get_value() == m_card_2.get_value());
}

void Hand::set_high_and_low_card_values()
{
    int card_1_value = m_card_1.get_value();
    int card_2_value = m_card_2.get_value();
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

bool Hand::operator<=(const Hand& hand) const
{
    if (m_is_pocket_pair ^ hand.get_is_pocket_pair())//If exactly one hand is a pocket pair.
    {
        return hand.get_is_pocket_pair();
    }
    else if (m_high_card_value == hand.get_high_card_value())
    {
        return m_low_card_value <= hand.get_low_card_value();
    }
    else 
    {   
        return m_high_card_value <= hand.get_high_card_value();
    }
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

Card  Hand::get_card(const int& x) const
{
    if (x == 1)
    {
        return m_card_1;
    }

    else if (x == 2)
    {
        return m_card_2;
    }   
    else
    {
        throw std::runtime_error("Error when exectuting get_card. Was expecting the integers 1 or 2, however instead recieved: " + std::to_string(x));
    }     
}

std::ostream& operator<<(std::ostream& stream, const Hand& hand)
{
    return stream << hand.get_card(1) << hand.get_card(2);
}