#include <iostream>
#include <vector>

class thing
{
    public:
    int m_x;
    thing(int x):m_x(x){}
};

class func
{
    public:
    std::vector<thing*>& m_v;
    func(std::vector<thing*>& v);
};