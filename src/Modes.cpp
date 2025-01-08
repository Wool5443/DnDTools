#include <fmt/format.h>
#include <fmt/ranges.h>

#include "Modes.hpp"
#include "Roll.hpp"

void RunDiceMode(DiceModeOptions options)
{
    for (int i = 0; i < options.count; i++)
    {
        auto row = ThrowDiceList(options.dice);
        fmt::println("{}", row);
    }
}

void RunStatsMode(StatsModeOptions options)
{
    for (int i = 0; i < options.columns; i++)
    {
        auto column = ThrowStatsColumn(options);
        fmt::println("{}", column);
    }
}
