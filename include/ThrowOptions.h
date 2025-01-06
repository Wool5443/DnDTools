#ifndef THROW_OPTIONS_H_
#define THROW_OPTIONS_H_

#include <stdio.h>
#include "Roll.h"

typedef DiceType* Stats;

typedef struct ThrowOptions
{
    DiceType dice;
    int      ndice;
    int      ncols;
    int      nstats;
    bool     rethrowOnes;
} ThrowOptions;

static ThrowOptions DEFAULT_STATS_MODE = {
    .dice        = 6,
    .ncols       = 2,
    .nstats      = 6,
    .rethrowOnes = false,
};

static ThrowOptions DEFAULT_DICE_MODE = {
    .dice  = 20,
    .ndice = 1,
};

void PrintThrowOptions(FILE* file, ThrowOptions opts);

#endif // THROW_OPTIONS_H_
