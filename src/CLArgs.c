#include <argp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "CLArgs.h"

#include "Error.h"
#include "Logger.h"

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

    ThrowStatOptions* opts = (ThrowStatOptions*)state->input;

    switch (key)
    {
        case 'd':
        {
            ParseIntContext context = parseInt(arg);
            if (*context.endptr != '\0')
            {
                err = EINVAL;
                LogError("Failed to parse int: %s, error at %s", arg, context.endptr);
                ERROR_LEAVE();
            }
            opts->type = context.value;
            break;
        }
        case 'c':
        {
            ParseIntContext context = parseInt(arg);
            if (*context.endptr != '\0')
            {
                err = EINVAL;
                LogError("Failed to parse int: %s, error at %s", arg, context.endptr);
                ERROR_LEAVE();
            }
            opts->ncols = context.value;
            break;
        }
        case 's':
        {
            ParseIntContext context = parseInt(arg);
            if (*context.endptr != '\0')
            {
                err = EINVAL;
                LogError("Failed to parse int: %s, error at %s", arg, context.endptr);
                ERROR_LEAVE();
            }
            opts->nstats = context.value;
            break;
        }
        case 'r':
            opts->rethrowOnes = true;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

ERROR_CASE
    return err;
}

ResultThrowStatOptions ParseCLArgs(int argc, const char* argv[])
{
    ERROR_CHECKING();

    const char* doc = "A simple stats thrower for DND";
    const char* argsDoc = "";

    struct argp_option parseOptions[] = {
        (struct argp_option){
            .name = "dice",
            .key  = 'd',
            .arg  = "type",
            .doc  = "Specify type of dice for throwing stats."
                    "Can be any integer.",
        },
        (struct argp_option){
            .name = "ncols",
            .key  = 'c',
            .arg  = "cols",
            .doc  = "Number of stat columns to throw."
        },
        (struct argp_option){
            .name = "nstats",
            .key  = 's',
            .arg  = "stats",
            .doc  = "Number of stats in a column."
        },
        (struct argp_option){
            .name = "rethrow-ones",
            .key  = 'r',
            .doc  = "If set than all ones are rethrow one time."
        },
        {},
    };

    struct argp parser = {
        .options  = parseOptions,
        .parser   = parseArg,
        .doc      = doc,
        .args_doc = argsDoc,
    };

    ThrowStatOptions throwOptions = DEFAULT_THROW_OPTIONS;

    int unparsedArg = 0;
    error_t parseErr = argp_parse(&parser, argc, (char**)argv, 0, &unparsedArg, &throwOptions);

    if (parseErr != 0)
    {
        err = ERROR_BAD_ARGS;
        LogError("Failed to parse %s: %s", argv[unparsedArg], strerror(parseErr));
        ERROR_LEAVE();
    }

    return ResultThrowStatOptionsCtor(throwOptions, EVERYTHING_FINE);
ERROR_CASE
    return ResultThrowStatOptionsCtor((ThrowStatOptions){}, err);
}
