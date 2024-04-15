#pragma once


#include "holdemprefloplogic.h"
#include "holdemui.h"

class PreFlopGame:public HoldEmPreFlopLogic, HoldEmUI 
{
public:
    PreFlopGame(std::vector<PokerPlayer>& players, Deck& deck, double small_blind, double big_blind);
    void run();


private:
    void play_pre_flop();
};