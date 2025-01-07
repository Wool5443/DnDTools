#ifndef DNDTOOLS_OPTIONS_HPP_
#define DNDTOOLS_OPTIONS_HPP_

#include <vector>
#include <ostream>
#include <format>
#include "Roll.hpp"

struct DiceModeOptions
{
    std::vector<DiceInt> dice;
    int count;

    DiceModeOptions() = default;

    DiceModeOptions(std::vector<DiceInt> dice, int count)
        : dice(std::move(dice)), count(count) {}

    friend std::ostream& operator<<(std::ostream& os, const DiceModeOptions& options)
    {
        for (auto d : options.dice)
        {
            os << std::format("{} ", d);
        }
        os << '\n';
        os << options.count;
        return os;
    }
};

struct StatsModeOptions
{
    DiceInt statsDice;
    int     statsCount;
    int     columns;
    bool    rethrowOnes;

    StatsModeOptions() = default;

    StatsModeOptions(DiceInt statsDice, int countStats, int columns, bool rethrowOnes)
        : statsDice(statsDice), statsCount(countStats), columns(columns),
          rethrowOnes(rethrowOnes) {}

    friend std::ostream& operator<<(std::ostream& os, const StatsModeOptions& options)
    {
        os << options.statsDice << '\n';
        os << options.statsCount << '\n';
        os << options.columns << '\n';
        os << options.rethrowOnes << '\n';
        return os;
    }
};

constexpr int DICE_PER_STAT = 4;

#endif // DNDTOOLS_OPTIONS_HPP_
