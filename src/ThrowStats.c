#include <limits.h>
#include <stdio.h>

#include "Vector.h"
#include "ThrowStats.h"

void ThrowStatColumn(Stats* stats, Options opts)
{
    for (int i = 0; i < opts.nstats; i++)
    {
        int sum = 0;
        int min = INT_MAX;
        for (size_t j = 0; j < 4; j++)
        {
            int roll = RollStatDice(opts.dice, opts.rethrowOnes);
            min = roll < min ? roll : min;
            sum += roll;
        }
        sum -= min;
        VecAdd(*stats, sum);
    }
}


void PrintStatColumn(FILE* file, Stats stats)
{
    assert(file);

    if (!stats || VecSize(stats) == 0)
    {
        LogDebug("Tried to print empty stats");
        return;
    }

    fprintf(file, "%d", stats[0]);
    for (int i = 1, end = VecSize(stats); i < end; i++)
    {
        fprintf(file, " %d", stats[i]);
    }
    fputc('\n', file);
}
