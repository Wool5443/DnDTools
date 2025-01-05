#include <limits.h>

#include "Vector.h"
#include "StatColumn.h"

DECLARE_RESULT_SOURCE(Stats);
DECLARE_RESULT_SOURCE(ThrowStatOptions);

void ThrowStatColumn(Stats* stats, ThrowStatOptions opts)
{
    for (int i = 0; i < opts.nstats; i++)
    {
        int sum = 0;
        int min = INT_MAX;
        for (size_t j = 0; j < 4; j++)
        {
            int roll = RollStatDice(opts.type, opts.rethrowOnes);
            min = roll < min ? roll : min;
            sum += roll;
        }
        sum -= min;
        VecAdd(*stats, sum);
    }
}


void PrintStatColumn(FILE* file, Stats stats)
{
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

