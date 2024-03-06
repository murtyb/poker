#include "misc.h"

bool is_element_of(const std::string& x, const std::vector<std::string>& v)
{
    for (std::string element : v)
    {
        if (element == x)
        {
            return true;
        }
    }
    return false;
}



void clear_cin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}