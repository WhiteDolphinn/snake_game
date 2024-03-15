#pragma once
#include <string.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "view.hpp"

const int length_game_name = 15;
const int num_of_rabbits = 5;


class Model
{
    private:
    View& view;
    char game_name[length_game_name] = {};
    void generate_rabbits();
    void generate_snakes();
    void update();

    std::list<Rabbit> rabbits;
    std::list<Snake> snakes;

    public:

    Model(View& view_)
    : view(view_)
    {
        generate_rabbits();
        generate_snakes();
    }

    void set_name(char* buff);
};
