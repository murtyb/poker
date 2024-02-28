#pragma once

#include <string>
#include <vector>
#include <map>

using std::string;


bool is_element_of(const string& x, const std::vector<string>& v);


class Card
{
public:
    Card(const string& card_symbol);

    static void card_initialization();
    
    int get_value() const;
    bool operator<=(const Card& card) const;

private:
    static std::map<string, int> s_face_card_values;
    static std::vector<string> s_face_cards;
    static std::vector<string> s_non_face_cards;

    string m_card_symbol;
    int m_card_value;

    static bool is_valid_face_card(const string& card_symbol);
    static bool is_valid_nonface_card(const string& card_symbol);
    static int value_of_face_symbol(const string &card_symbol);
    static void invalid_symbol_error(const string& invalid_symbol, const std::vector<string>& valid_symbol);
    
};
