#pragma once

#include <string>
#include <cmath>
#include <map>
#include <stdexcept>


class Chips
{
public:
    int m_num_of_chips;
    float m_num_of_bb;

    static int s_bb;
    static int s_sb;
    Chips();
    Chips(float num_of_bb, char currency);
    Chips remainder(int x);
    void operator+=(const Chips& chips);
    void operator-=(const Chips& chips);
    bool operator<=(const Chips& chips) const;
    bool operator==(const Chips &chips) const;
    Chips operator/(int x) const;
    Chips operator-(Chips chips) const;
    Chips operator+(Chips chips) const;

    std::string bb_string();

private:
    static const int m_bb_precision = 2;
    static int num_of_chips(float amnt, char currency);
    static std::map<std::string, char> s_currency_map;
    static float num_of_bb(float amnt, char currency);
    void update_bb();
};