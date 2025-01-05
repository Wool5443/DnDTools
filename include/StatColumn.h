#ifndef STAT_COLUMN_H_
#define STAT_COLUMN_H_

#include "Result.h"
#include "Roll.h"

typedef int* Stats;

DECLARE_RESULT_HEADER(Stats);

typedef struct ThrowStatOptions
{
    DiceType type;
    int      ncols;
    int      nstats;
    bool     rethrowOnes;
} ThrowStatOptions ;
DECLARE_RESULT_HEADER(ThrowStatOptions);

static ThrowStatOptions DEFAULT_THROW_OPTIONS = {
    .type        = 6,
    .ncols       = 2,
    .nstats      = 6,
    .rethrowOnes = false,
};

void ThrowStatColumn(Stats* stats, ThrowStatOptions opts);
void PrintStatColumn(FILE* file, Stats stats);

#endif // STAT_COLUMN_H_
