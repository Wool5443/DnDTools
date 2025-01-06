#ifndef APP_STATE_H_
#define APP_STATE_H_

#include "Result.h"
#include "ThrowOptions.h"

typedef enum AppMode
{
    DICE_MODE,
    STATS_MODE,
    APP_MODE_COUNT,
} AppMode;

static const char* AppModeNames[] = {
    "dice",
    "stats",
};

typedef struct AppState
{
    AppMode      mode;
    ThrowOptions throwOptions;
} AppState;

DECLARE_RESULT_HEADER(AppState);

#endif // APP_STATE_H_
