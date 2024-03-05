#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include "Player.h"

bool is_element_of(const std::string& x, const std::vector<std::string>& v);

bool is_element_of(const Player& x, const std::vector<Player>& v);

void clear_cin();