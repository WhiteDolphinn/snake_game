#pragma once
#include <string.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "view.hpp"

const int length_game_name = 15;
const int FPS = 5;

class Model
{
    private:
    char game_name[length_game_name] = {};
    void generate_rabbits();
    void generate_snakes();
    void update_snake(std::list<Snake>::iterator snake);

    void end_game();
    bool is_game_goes = true;

    int num_of_rabbits = 5;
    int num_of_bots = 2;

    public:
    View& view;
    std::list<Rabbit> rabbits;
    std::list<Snake> snakes;

    Model(View& view_, int num_of_bots_ = 2, int num_of_rabbits_ = 5)
    : view(view_)
    {
        num_of_bots = num_of_bots_;
        num_of_rabbits = num_of_rabbits_;
        generate_rabbits();
        generate_snakes();
    }

    void set_name(char* buff);
    void update();
};

enum direction
{
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
};
