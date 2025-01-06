#include "Vector.h"
#include "ModeFunctions.h"
#include "ThrowStats.h"

ErrorCode DiceMode(AppState state)
{
    if (state.throwOptions.ndice == 0)
    {
        printf("Throwing 0 dices...\n");
        return EVERYTHING_FINE;
    }

    srand(time(NULL));

    int roll = RollDice(state.throwOptions.dice);
    printf("%d", roll);

    for (int i = 1; i < state.throwOptions.ndice; i++)
    {
        roll = RollDice(state.throwOptions.dice);
        printf(" %d", roll);
    }

    fputc('\n', stdout);

    return EVERYTHING_FINE;
}

ErrorCode StatsMode(AppState state)
{
    ERROR_CHECKING();

    Stats stats = {};

    CHECK_ERROR(VecExpand(stats, state.throwOptions.nstats));

    srand(time(NULL));

    for (int i = 0; i < state.throwOptions.ncols; i++)
    {
        ThrowStatColumn(&stats, state.throwOptions);
        PrintStatColumn(stdout, stats);
        VecClear(stats);
    }

ERROR_CASE
    VecDtor(stats);

    return err;
}
