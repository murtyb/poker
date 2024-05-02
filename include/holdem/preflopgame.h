#pragma once


#include "holdemprefloplogic.h"
#include "holdemui.h"

class PreFlopGame:public HoldEmPreFlopLogic, HoldEmUI 
{
public:
    PreFlopGame(PokerPlayerGroup& players, Deck& deck, Chips small_blind, Chips big_blind);
    void run();


private:
    void play_pre_flop();
};