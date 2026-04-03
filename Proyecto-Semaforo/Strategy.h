#pragma once
#include "Fork.h"

class Strategy {
public:
    virtual void comer(int id, Fork& left, Fork& right) = 0;
    virtual ~Strategy() = default;
};
