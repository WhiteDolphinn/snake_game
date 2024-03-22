#pragma once
#include <string.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "view.hpp"

const int length_game_name = 15;
const int num_of_rabbits = 5;
const int FPS = 5;

class Model
{
    private:
    char game_name[length_game_name] = {};
    void generate_rabbits();
    void generate_snakes();
    void update();


    public:
    View& view;
    std::list<Rabbit> rabbits;
    std::list<Snake> snakes;

    Model(View& view_)
    : view(view_)
    {
        generate_rabbits();
        generate_snakes();
    }

    void set_name(char* buff);
};

enum direction
{
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
};
