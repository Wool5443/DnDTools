#include <iostream>
#include "ParseCLI.hpp"
#include "Modes.hpp"

int main(int argc, const char* argv[])
{
    try
    {
        auto opts = ParseCLI(argc, argv).value();

        std::visit(ModeVisitor(), opts);
    }
    catch (const OptionsExitProgram& e) {}
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
