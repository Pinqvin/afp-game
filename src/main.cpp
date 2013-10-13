#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "application.hpp"

int main()
{
    try
    {
        AFP::Application game;
        game.run();

    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;

    }

    return EXIT_SUCCESS;

}

