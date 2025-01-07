#ifndef DNDTOOLS_PARSECLI_HPP_
#define DNDTOOLS_PARSECLI_HPP_

#include <variant>
#include <optional>

#include "Options.hpp"

class OptionsExitProgram : public std::exception
{};

using ModeOptions = std::variant<DiceModeOptions, StatsModeOptions>;
enum class Modes
{
    DICE,
    STATS,
    BAD,
};

std::optional<ModeOptions> ParseCLI(int argc, const char* argv[]);

#endif // DNDTOOLS_PARSECLI_HPP_
