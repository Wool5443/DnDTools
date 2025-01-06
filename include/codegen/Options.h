// DEF_OPTION(optname, optkey, optarg, optdoc, optparsecode)

#define PARSE_INT_OPTION(optfield)                          \
{                                                           \
    ParseIntContext context = parseInt(arg);                \
    if (*context.endptr != '\0')                            \
    {                                                       \
        err = EINVAL;                                       \
        LogError(                                           \
            "Failed to parse int: %s, error at %s",         \
            arg, context.endptr);                           \
        ERROR_LEAVE();                                      \
    }                                                       \
    optfield = context.value;                               \
}

#define PARSE_BOOL_OPTION(optfield)                         \
{                                                           \
    optfield = true;                                        \
}


DEF_OPTION(
    "dice",
    'd',
    "type",
    "Specify type of dice for throwing stats. Can be any integer.",
    PARSE_INT_OPTION(opts->dice)
)

DEF_OPTION(
    "ncols",
    'c',
    "cols",
    "Number of stat columns to throw.",
    PARSE_INT_OPTION(opts->ncols)
)

DEF_OPTION(
    "nstats",
    's',
    "stats",
    "Number of stats in a column.",
    PARSE_INT_OPTION(opts->nstats)
)

DEF_OPTION(
    "rethrow-ones",
    'r',
    NULL,
    "If set than all ones are rethrow one time.",
    PARSE_BOOL_OPTION(opts->rethrowOnes)
)

#undef PARSE_INT_OPTION
#undef PARSE_BOOL_OPTION