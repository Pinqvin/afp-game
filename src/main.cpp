#include "game.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        AFP::Game game;
        game.run();

    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;

    }

    return EXIT_SUCCESS;

}

