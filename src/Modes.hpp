#ifndef DNDTOOLS_MODES_HPP_
#define DNDTOOLS_MODES_HPP_

#include "Options.hpp"

void RunDiceMode (DiceModeOptions  options);
void RunStatsMode(StatsModeOptions options);

class ModeVisitor
{
public:
    void operator()(DiceModeOptions options)
    {
        RunDiceMode(options);
    }

    void operator()(StatsModeOptions options)
    {
        RunStatsMode(options);
    }
};

#endif // DNDTOOLS_MODES_HPP_
