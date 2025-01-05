#include <stdlib.h>

#include "Roll.h"

int RollDice(DiceType type)
{
    return 1 + rand() % type;
}

int RollStatDice(DiceType type, bool rethrowOne)
{
    int val = RollDice(type);

    if (rethrowOne && val == 1)
    {
        val = RollDice(type);
    }

    return val;
}

