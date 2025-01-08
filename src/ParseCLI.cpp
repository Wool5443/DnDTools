#include <boost/program_options.hpp>
#include <fmt/ostream.h>

#include "ParseCLI.hpp"

namespace po = boost::program_options;

constexpr DiceInt DEFAULT_DICE_MODE_DICE = 20;
constexpr DiceInt DEFAULT_STATS_MODE_DICE = 6;

constexpr int DEFAULT_STATS_COUNT = 6;
constexpr int DEFAULT_COLS_COUNT = 2;

class OptionsHierarchy
{
public:
    OptionsHierarchy()
    {
        m_helpOptions.add_options()
            ("help,h", "produce help message");

        m_chooseModeOptions.add_options()
            ("dice-mode",
             po::bool_switch(),
             "how many dice to throw")
            ("stats-mode",
             po::bool_switch(),
             "how many dice to throw");

        m_diceModeOptions.add_options()
            ("dice",
             po::value<std::vector<DiceInt>>(),
             "list of dice to throw in dice mode or 1d6 if not specified")
            ("count",
             po::value<int>()->default_value(1),
             "how many dice to throw in dice mode");

        m_statsModeOptions.add_options()
            ("stats-dice",
             po::value<DiceInt>()->default_value(DEFAULT_STATS_MODE_DICE),
             "dice to throw for stats in stats mode")
            ("stats",
             po::value<int>()->default_value(DEFAULT_STATS_COUNT),
             "how many stats to throw in stats mode")
            ("cols",
             po::value<int>()->default_value(DEFAULT_COLS_COUNT),
             "how many columns to throw in stats mode")
            ("rethrow-ones",
             po::bool_switch(),
             "rethrow \"ones\" one time in stats mode");

        m_cmdOptions
            .add(m_chooseModeOptions)
            .add(m_diceModeOptions)
            .add(m_statsModeOptions);

        m_positionalOptions.add("dice", -1);
    }

    Modes GetMode()
    {
        unsigned dice  = m_vm["dice-mode"].as<bool>() << 1;
        unsigned stats = m_vm["stats-mode"].as<bool>();

        unsigned res = dice | stats;

        if (res == dice)
        {
            return Modes::DICE;
        }
        if (res == stats)
        {
            return Modes::STATS;
        }

        return Modes::BAD;
    }

    std::vector<DiceInt> GetDice()
    {
        if (m_vm.count("dice"))
        {
            return m_vm["dice"].as<std::vector<DiceInt>>();
        }

        return { DEFAULT_DICE_MODE_DICE };
    }

    int GetCount()
    {
        return m_vm["count"].as<int>();
    }

    DiceInt GetStatsDice()
    {
        return m_vm["stats-dice"].as<DiceInt>();
    }

    int GetStats()
    {
        return m_vm["stats"].as<int>();
    }

    int GetColumns()
    {
        return m_vm["cols"].as<int>();
    }

    bool GetRethrowOnes()
    {
        return m_vm["rethrow-ones"].as<bool>();
    }

    void Parse(int argc, const char* argv[])
    {
        po::options_description opts;
        opts.add(m_cmdOptions).add(m_hiddenCmdOptions).add(m_helpOptions);
        po::store(po::command_line_parser(argc, argv)
                  .options(opts).positional(m_positionalOptions).run(), m_vm);
        po::notify(m_vm);

        CheckHelp();
    }

private:
    void CheckHelp()
    {
        if (m_vm.count("help"))
        {
            PrintHelp();
            throw OptionsExitProgram();
        }
    }

    void PrintHelp()
    {
        fmt::print("{}", fmt::streamed(m_helpOptions));
        fmt::print("{}", fmt::streamed(m_chooseModeOptions));
        fmt::print("{}", fmt::streamed(m_diceModeOptions));
        fmt::print("{}", fmt::streamed(m_statsModeOptions));
    }

    po::options_description m_helpOptions      {"Generic options"};
    po::options_description m_chooseModeOptions{"Choose mode options"};
    po::options_description m_diceModeOptions  {"Dice mode options"};
    po::options_description m_statsModeOptions {"Stats mode options"};
    po::options_description m_cmdOptions;
    po::options_description m_hiddenCmdOptions;
    po::positional_options_description m_positionalOptions;

    po::variables_map m_vm;
};

std::optional<ModeOptions> ParseCLI(int argc, const char** argv)
{
    OptionsHierarchy h;
    h.Parse(argc, argv);

    Modes mode = h.GetMode();

    ModeOptions opts;

    switch (mode)
    {
        case Modes::DICE:
            opts.emplace<DiceModeOptions>(
                h.GetDice(),
                h.GetCount()
            );
            break;
        case Modes::STATS:
            opts.emplace<StatsModeOptions>(
                h.GetStatsDice(),
                h.GetStats(),
                h.GetColumns(),
                h.GetRethrowOnes()
            );
            break;
        default:
            throw std::runtime_error("Bad mode");
    }

    return opts;
}
