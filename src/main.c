#include <limits.h>
#include <argp.h>

#include "Vector.h"
#include "CLArgs.h"
#include "ModeFunctions.h" // IWYU pragma: keep

int CompareInt(const void* a, const void* b);

int main(int argc, const char* argv[])
{
    ERROR_CHECKING();

    LoggerInitConsole();

    Stats stats = {};

    ResultAppState stateRes = ParseCLArgs(argc, argv);
    CHECK_ERROR(stateRes.errorCode);
    AppState state = stateRes.value;

    PrintThrowOptions(stdout, state.throwOptions);

    switch (state.mode)
    {
        case DICE_MODE:
            CHECK_ERROR(DiceMode(state));
            break;
        case STATS_MODE:
            CHECK_ERROR(StatsMode(state));
            break;
        default:
            err = ERROR_BAD_VALUE;
            LogError("Error bad mode: %d", state.mode);
            ERROR_LEAVE();
    }

ERROR_CASE
    VecDtor(stats);

    LoggerFinish();

    return err;
}
