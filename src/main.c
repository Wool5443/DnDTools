#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <argp.h>

#include "Logger.h"
#include "Vector.h"
#include "StatColumn.h"
#include "CLArgs.h"

int CompareInt(const void* a, const void* b);

int main(int argc, const char* argv[])
{
    ERROR_CHECKING();

    LoggerInitConsole();

    Stats stats = {};

    ResultThrowStatOptions throwOptionsRes = ParseCLArgs(argc, argv);
    CHECK_ERROR(throwOptionsRes.errorCode);
    ThrowStatOptions throwOptions = throwOptionsRes.value;

    CHECK_ERROR(VecExpand(stats, throwOptions.nstats));

    srand(time(NULL));

    for (int i = 0; i < throwOptions.ncols; i++)
    {
        ThrowStatColumn(&stats, throwOptions);
        PrintStatColumn(stdout, stats);
        VecClear(stats);
    }

ERROR_CASE
    VecDtor(stats);

    LoggerFinish();

    return err;
}
