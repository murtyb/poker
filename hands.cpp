#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include "hands.h"


Hand::Hand(const Card& card_1, const Card& card_2)
    : m_card_1(card_1), m_card_2(card_2)
{
    m_is_pocket_pair = hand_is_pocket_pair();
    m_high_card_value = highest_card_value();
}        

bool Hand::hand_is_pocket_pair()
{
    return (m_card_1.get_value() == m_card_2.get_value());
}

int Hand::highest_card_value()
{
    int card_1_value = m_card_1.get_value();
    int card_2_value = m_card_2.get_value();
    if (card_1_value > card_2_value)
    {
        return card_1_value;
    }
    else
    {
        return card_2_value;
    }
}

bool Hand::operator<=(const Hand& hand) const
{
    if(m_is_pocket_pair ^ hand.get_is_pocket_pair())
    {
        return hand.get_is_pocket_pair();
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

bool Hand::get_high_card_value() const
    {
        return m_high_card_value;        
    }

Card  Hand::get_card(int& x) const
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