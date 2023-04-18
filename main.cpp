/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** main
*/

#include <iostream>
#include <Command.hpp>
#include "Reception.hpp"

static void initProgram(char *numberCook, char *timeCook, char *multiplier)
{
    plazza::Reception Reception(atoi(numberCook), atoi(timeCook), atoi(multiplier));

    Reception.initAll();
}

int main(int argc, char **argv)
{
    try {
        if (argc != 4) {
            std::cerr << "Error bad argument\n";
            return 84;
        }
        initProgram(argv[2], argv[3], argv[1]);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}