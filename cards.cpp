#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cards.h"
#include <map>

using std::string;

bool is_element_of(const string& x, const std::vector<string>& v)
{
    for (string element : v)
    {
        if (element == x)
        {
            return true;
        }
    }
    return false;
}


Card::Card(const string& card_symbol)
{
    m_card_symbol = card_symbol;
    
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
        std::vector<string> all_cards = s_non_face_cards;
        all_cards.insert(all_cards.end(), face_cards.begin(), face_cards.end());
        invalid_symbol_error(card_symbol, all_cards);
    }
}

bool Card::is_valid_face_card(const string& card_symbol)
{
    return is_element_of(card_symbol, face_cards);
}

bool Card::is_valid_nonface_card(const string& card_symbol)
{
    return is_element_of(card_symbol, s_non_face_cards);
}

int Card::value_of_face_symbol(const string& card_symbol)
{
    for (const auto& [symbol, value] : face_card_values)
    {
        if (card_symbol == symbol)
        {
            return value;
        }
    }
    invalid_symbol_error(card_symbol, face_cards);
    return -1;    
}

void Card::invalid_symbol_error(const string& invalid_symbol, const std::vector<string>& valid_symbols)
{
    string error_message = "Was expecting one of the strings: ";
    for (string symbol : valid_symbols)
    {
        error_message += "\"" + symbol + "\", ";
    }
    error_message.erase(error_message.length() - 2);
    error_message += ". However instead receaved: \"" + invalid_symbol + "\".";
    throw std::runtime_error(error_message);
}

int Card::get_value()
{
    return m_card_value;
}

void Card::card_initialization()
{
    face_card_values = {{"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};
    s_non_face_cards = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};
    for (const auto& pair : face_card_values)
    {
        face_cards.push_back(pair.first);
    }
}

std::vector<string> Card::face_cards;
std::map<string, int> Card::face_card_values;
std::vector<string> Card::s_non_face_cards;
