#include <argp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CLArgs.h"
#include "Logger.h"

#define PARSE_INT_OPTION(optfield)                          \
{                                                           \
    ParseIntContext context = parseInt(arg);                \
    if (*context.endptr != '\0')                            \
    {                                                       \
        err = EINVAL;                                       \
        LogError("Failed to parse int: %s, error at %s",    \
                 arg, context.endptr);                      \
        return err;                                         \
    }                                                       \
    optfield = context.value;                               \
}

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

    return (ParseIntContext){.value = value, .endptr = endptr};
}

static Options setDefaults(AppState state, Options defaultOpts)
{
    Options newOpts = state.options;

    if (!newOpts.dice)        newOpts.dice        = defaultOpts.dice;
    if (!newOpts.ndice)       newOpts.ndice       = defaultOpts.ndice;
    if (!newOpts.ncols)       newOpts.ncols       = defaultOpts.ncols;
    if (!newOpts.nstats)      newOpts.nstats      = defaultOpts.nstats;
    if (!newOpts.rethrowOnes) newOpts.rethrowOnes = defaultOpts.rethrowOnes;

    return newOpts;
}

static error_t parseArg(int key, char* arg, struct argp_state* state)
{
    ERROR_CHECKING();

    assert(state);

    AppState* appState = (AppState*)state->input;

    switch (key)
    {
        case 'd': // dice
        {
            PARSE_INT_OPTION(appState->options.dice);
            return EVERYTHING_FINE;
        }
        case 'n': // dice
        {
            PARSE_INT_OPTION(appState->options.ndice);
            return EVERYTHING_FINE;
        }
        case 'c': // dice
        {
            PARSE_INT_OPTION(appState->options.ncols);
            return EVERYTHING_FINE;
        }
        case 's': // dice
        {
            PARSE_INT_OPTION(appState->options.nstats);
            return EVERYTHING_FINE;
        }

        case ARGP_KEY_ARG:
        {
            if (state->arg_num > 1)
            {
                err = EINVAL;
                LogError("Give only one positional option to select mode.");
                return err;
            }

            for (int i = 0; i < APP_MODE_COUNT; i++)
            {
                if (strcmp(arg, AppModeNames[i]) == 0)
                {
                    appState->mode = i;
                    return EVERYTHING_FINE;
                }
            }

            err = EINVAL;
            LogError("Invalid mode %s", arg);
            return err;
        }
    default:
        return ARGP_ERR_UNKNOWN;
    }
}

ResultAppState ParseCLArgs(int argc, const char* argv[])
{
    ERROR_CHECKING();

    const char* doc = "A simple stats thrower for DND";
    const char* argsDoc = "";

    struct argp_option parseOptions[] = {
        (struct argp_option){
            .name = "dice",
            .key = 'd',
            .arg = "type",
            .doc = "Specify type of dice for throwing stats. Can be any integer.",
        },
        (struct argp_option){
            .name = "ndice",
            .key = 'n',
            .arg = "dice count",
            .doc = "How much dice to throw.",
        },
        (struct argp_option){
            .name = "ncols",
            .key = 'c',
            .arg = "cols",
            .doc = "Number of stat columns to throw.",
        },
        (struct argp_option){
            .name = "nstats",
            .key = 's',
            .arg = "stats",
            .doc = "Number of stats in a column.",
        },
        (struct argp_option){
            .name = "rethrow-ones",
            .key = 'r',
            .arg = NULL,
            .doc = "If set than all ones are rethrow one time.",
        },
        {},
    };

    struct argp parser = {
        .options = parseOptions,
        .parser = parseArg,
        .doc = doc,
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

    switch (state.mode)
    {
    case DICE_MODE:
        state.options = setDefaults(state, DEFAULT_DICE_MODE);
        break;
    case STATS_MODE:
        state.options = setDefaults(state, DEFAULT_STATS_MODE);
        break;
    default:
        err = ERROR_BAD_VALUE;
        LogError("Bad mode: %d", state.mode);
        ERROR_LEAVE();
    }

    return ResultAppStateCtor(state, EVERYTHING_FINE);
    ERROR_CASE
    return ResultAppStateCtor((AppState){}, err);
}
