#ifndef DNDTOOLS_ROLL_HPP_
#define DNDTOOLS_ROLL_HPP_

#include "Options.hpp"

DiceInt RollDice    (DiceInt maxValue);
DiceInt RollStatDice(DiceInt maxValue, bool rethrowOne);

std::vector<DiceInt> ThrowDiceList(std::span<const DiceInt> dice);
std::vector<DiceInt> ThrowStatsColumn(StatsModeOptions options);

#endif // DNDTOOLS_ROLL_HPP_
