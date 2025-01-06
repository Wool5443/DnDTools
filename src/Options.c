#include <limits.h>
#include <assert.h>

#include "Options.h"

void PrintOptions(FILE* file, Options opts)
{
    assert(file);

    fprintf(file,
            "dice:        %d\n"
            "ndice:       %d\n"
            "ncols:       %d\n"
            "nstats:      %d\n"
            "rethrowOnes: %d\n",
            opts.dice,
            opts.ndice,
            opts.ncols,
            opts.nstats,
            opts.rethrowOnes
    );
}
