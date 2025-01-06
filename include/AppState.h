#ifndef APP_STATE_H_
#define APP_STATE_H_

#include "Result.h"
#include "ThrowOptions.h"

typedef enum AppMode
{

#define DEF_MODE(mode, ...) mode,

#include "codegen/Modes.h"

#undef DEF_MODE

} AppMode;

typedef struct AppState
{
    AppMode      mode;
    ThrowOptions throwOptions;
} AppState;

DECLARE_RESULT_HEADER(AppState);

#endif // APP_STATE_H_
