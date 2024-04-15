#include "..\..\include\chips\chips.h"

Chips::Chips(int num_of_chips)
    : m_num_of_chips(num_of_chips),
      m_num_of_bb(float(num_of_chips)/s_bb)
{
}

void Chips::update_bb()
{
    m_num_of_bb = float(m_num_of_chips)/s_bb;
}

void Chips::operator+=(Chips chips)
{
    m_num_of_chips += chips.m_num_of_chips;
    update_bb();
}

void Chips::operator-=(Chips chips)
{
    m_num_of_chips -= chips.m_num_of_chips;
    update_bb();
}

std::string Chips::bb_string()
{
    std::string no_dec_point;
    float bb_rnded = std::round(m_num_of_bb * std::pow(10, m_bb_precision)) / std::pow(10, m_bb_precision);
    if (int(bb_rnded) == bb_rnded) {return std::to_string(int(bb_rnded));}
    for (int i = 1; i <= m_bb_precision; i++)
    {
        float x = std::pow(10, i) * bb_rnded;
        if (int(x) == x)
        {
            no_dec_point = std::to_string(int(x));
            break;
        }
    }
    if (bb_rnded < 1) {return "0." + no_dec_point;}
    int ordr_of_mag = std::to_string(int(bb_rnded)).size();
    return no_dec_point.insert(ordr_of_mag, 1, '.');
}