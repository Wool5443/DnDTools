#ifndef DNDTOOLS_ROLL_HPP_
#define DNDTOOLS_ROLL_HPP_

using DiceInt = unsigned;

DiceInt RollDice    (DiceInt maxValue);
DiceInt RollStatDice(DiceInt maxValue, bool rethrowOne);

#endif // DNDTOOLS_ROLL_HPP_
