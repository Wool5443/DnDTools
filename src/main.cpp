#include <iostream>
#include "ParseCLI.hpp"
#include "Modes.hpp"

int main(int argc, const char* argv[])
{
    try
    {
        auto opts = *ParseCLI(argc, argv);

        if (DiceModeOptions* dice = std::get_if<DiceModeOptions>(&opts))
        {
            RunDiceMode(*dice);
        }
        else if (StatsModeOptions* stats = std::get_if<StatsModeOptions>(&opts))
        {
            RunStatsMode(*stats);
        }
    }
    catch (const OptionsExitProgram& e) {}
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
