#pragma once
#include "Header.h"
#include "Entity.h"

class player : public Entity
{
public:
    bool thrust;

    player();

    void update();

};

