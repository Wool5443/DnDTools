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

#define DEF_MODE(modmode, modname, moddefaultstate, modfunction, ...)   \
case modmode:                                                           \
{                                                                       \
    modfunction(state);                                                 \
    break;                                                              \
}

#include "codegen/Modes.h"

#undef DEF_MODE

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
