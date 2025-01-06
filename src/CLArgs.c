#include <argp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
#define DEF_OPTION(optname, optkey, optarg, optdoc, optparseCode, ...)  \
case optkey:                                                            \
{                                                                       \
    optparseCode                                                        \
    break;                                                              \
}

#include "codegen/Options.h"

#undef DEF_OPTION
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
