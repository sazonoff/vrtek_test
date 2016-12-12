#pragma once


#include "AbstractItem.h"


namespace evil
{
    
    enum class RareType : unsigned char
    {
        Jug,
        Helm,
        Coin,
        Sword,
    };

    struct Jug
        : AbstractItem
    {
        Size R;
        Size H;
    };

    struct Helm
        : AbstractItem
    {
        Size  size;
        Value armor;
    };

    struct Coin
        : AbstractItem
    {
    };

    struct Sword
        : AbstractItem
    {
        Value damage;
        Value height;
    };


}
