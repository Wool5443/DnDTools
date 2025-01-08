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

std::vector<DiceInt> ThrowDiceList(std::span<const DiceInt> dice)
{
    std::vector<DiceInt> result;
    result.reserve(dice.size());

    for (auto d : dice)
    {
        result.push_back(RollDice(d));
    }

    return result;
}

std::vector<DiceInt> ThrowStatsColumn(StatsModeOptions options)
{
    std::vector<DiceInt> result;
    result.reserve(options.statsCount);

    for (int i = 0; i < options.statsCount; i++)
    {
        DiceInt sum = 0;
        DiceInt min = std::numeric_limits<DiceInt>::max();
        for (int i = 0; i < DICE_PER_STAT; i++)
        {
            DiceInt roll = RollStatDice(options.statsDice, options.rethrowOnes);
            min = roll < min ? roll : min;
            sum += roll;
        }
        sum -= min;

        result.push_back(sum);
    }

    return result;
}

