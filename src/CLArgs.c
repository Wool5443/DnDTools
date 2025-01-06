#include <argp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "CLArgs.h"

#include "Logger.h"

DECLARE_RESULT_SOURCE(AppState);

typedef struct ParseIntContext
{
    char* endptr;
    int value;
} ParseIntContext;

static ParseIntContext parseInt(const char* str)
{
    char* endptr = NULL;
    int value = strtol(str, &endptr, 10);

    return (ParseIntContext){ .value = value, .endptr = endptr };
}

static error_t parseArg(int key, char* arg, struct argp_state* state)
{
    ERROR_CHECKING();

    assert(state);

    AppState* opts = (AppState*)state->input;

    LogDebug("key(%d): %c\narg: %s", key, key, arg);

    switch (key)
    {
#define DEF_OPTION(optname, optkey, optarg, optdoc, optparseCode, ...)  \
case optkey:                                                            \
{                                                                       \
    optparseCode                                                        \
    break;                                                              \
}

#include "codegen/Options.h"

#undef DEF_OPTION

        case ARGP_KEY_ARG:
        {
            if (state->arg_num > 1)
            {
                err = EINVAL;
                LogError("Give only one positional option to select mode.");
                ERROR_LEAVE();
            }

#define DEF_MODE(modmode, modname, moddefaultstate, ...)                \
if (strcmp(arg, modname) == 0)                                          \
{                                                                       \
    opts->mode         = modmode;                                       \
    opts->throwOptions = moddefaultstate;                               \
}                                                                       \
else

#include "codegen/Modes.h"

#undef DEF_MODE

         // else
            {
                err = EINVAL;
                LogError("Invalid mode %s", arg);
                ERROR_LEAVE();
            }
            LogDebug("Anal");
            break;
        }
        default:
            return ARGP_ERR_UNKNOWN;
    }

ERROR_CASE
    return err;
}

ResultAppState ParseCLArgs(int argc, const char* argv[])
{
    ERROR_CHECKING();

    const char* doc = "A simple stats thrower for DND";
    const char* argsDoc = "";

    struct argp_option parseOptions[] = {

#define DEF_OPTION(optname, optkey, optarg, optdoc, ...)    \
(struct argp_option) {                                      \
    .name = optname,                                        \
    .key  = optkey,                                         \
    .arg  = optarg,                                         \
    .doc  = optdoc,                                         \
},

#include "codegen/Options.h"

#undef DEF_OPTION
        {},
    };

    struct argp parser = {
        .options  = parseOptions,
        .parser   = parseArg,
        .doc      = doc,
        .args_doc = argsDoc,
    };

    AppState state = {};

    int unparsedArg = 0;
    error_t parseErr = argp_parse(&parser, argc, (char**)argv, 0, &unparsedArg, &state);

    if (parseErr != 0)
    {
        err = ERROR_BAD_ARGS;
        LogError("Failed to parse %s: %s", argv[unparsedArg], strerror(parseErr));
        ERROR_LEAVE();
    }

    return ResultAppStateCtor(state, EVERYTHING_FINE);
ERROR_CASE
    return ResultAppStateCtor((AppState){}, err);
}
