#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "..\..\include\cards\cards.h"



using std::string;


Card::Card(const std::string& card_symbol)
    :m_card_symbol(card_symbol)
{
    if (is_valid_nonface_card(card_symbol))
    {
        m_card_value = std::stoi(card_symbol);
    }
    else if (is_valid_face_card(card_symbol))
    {
        m_card_value = value_of_face_symbol(card_symbol);
    }
    else
    {
        std::vector<std::string> all_cards = s_non_face_cards;
        all_cards.insert(all_cards.end(), s_face_cards.begin(), s_face_cards.end());
        invalid_symbol_error(card_symbol, all_cards);
    }
}

bool Card::is_valid_face_card(const std::string& card_symbol)
{
    return is_element_of(card_symbol, s_face_cards);
}

bool Card::is_valid_nonface_card(const std::string& card_symbol)
{
    return is_element_of(card_symbol, s_non_face_cards);
}

int Card::value_of_face_symbol(const std::string& card_symbol)
{
    for (const auto& [symbol, value] : s_face_card_values)
    {
        if (card_symbol == symbol)
        {
            return value;
        }
    }
    invalid_symbol_error(card_symbol, s_face_cards);
    return -1;    
}

void Card::invalid_symbol_error(const std::string& invalid_symbol, const std::vector<std::string>& valid_symbols)
{
    std::string error_message = "Was expecting one of the strings: ";
    for (string symbol : valid_symbols)
    {
        error_message += "\"" + symbol + "\", ";
    }
    error_message.erase(error_message.length() - 2);
    error_message += ". However instead receaved: \"" + invalid_symbol + "\".";
    throw std::runtime_error(error_message);
}

int Card::get_value() const
{
    return m_card_value;
}

std::string Card::get_symbol() const
{
    return m_card_symbol;
}

void Card::card_initialization()
{
    s_face_card_values = {{"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};
    s_non_face_cards = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};
    for (const auto& pair : s_face_card_values)
    {
        s_face_cards.push_back(pair.first);
    }
}

bool Card::operator<=(const Card& card) const
{
    return m_card_value <= card.get_value();
}

std::ostream& operator<<(std::ostream& stream, const Card& card)
{
    return stream << card.m_card_symbol;
}

std::vector<std::string> Card::s_face_cards;
std::map<std::string, int> Card::s_face_card_values;
std::vector<std::string> Card::s_non_face_cards;
