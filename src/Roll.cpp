#include <random>
#include "Roll.hpp"

DiceInt RollDice(DiceInt maxValue)
{
    static std::random_device rd;
    static std::mt19937_64 gen(rd());

    std::uniform_int_distribution<DiceInt> distr(1, maxValue);

    return distr(gen);
}

DiceInt RollStatDice(DiceInt type, bool rethrowOne)
{
    DiceInt val = RollDice(type);

    if (rethrowOne && val == 1)
    {
        val = RollDice(type);
    }

    return val;
}

