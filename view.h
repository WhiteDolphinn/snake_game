#pragma once
#include <iostream>

class View
{
    public:
    void print_game_name(char* game_name)
    {
        std::cout << "Game: " << game_name << std::endl;
    }
};
