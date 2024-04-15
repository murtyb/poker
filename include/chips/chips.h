#pragma once

#include <string>
#include <cmath>
class Chips
{
public:
    int m_num_of_chips;
    float m_num_of_bb;

    static int s_bb;
    static int s_sb;

    Chips(int x);
    void operator+=(Chips chips);
    void operator-=(Chips chips);
    std::string bb_string();

private:
static const int m_bb_precision = 2;
    void update_bb();
};