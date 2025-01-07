#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include "Modes.hpp"

static std::vector<DiceInt> throwDice(std::span<const DiceInt> dice)
{
    std::vector<DiceInt> result;
    result.reserve(dice.size());

    for (auto d : dice)
    {
        result.push_back(RollDice(d));
    }

    return result;
}

static std::vector<DiceInt> throwStats(StatsModeOptions options)
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

void RunDiceMode(DiceModeOptions options)
{
    for (int i = 0; i < options.count; i++)
    {
        auto row = throwDice(options.dice);

        fmt::print("{}\n", row);
    }
}

void RunStatsMode(StatsModeOptions options)
{
    for (int i = 0; i < options.columns; i++)
    {
        auto column = throwStats(options);
        fmt::println("{}", column);
    }
}
