#pragma once
#include <string.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "view.hpp"

const int length_game_name = 15;
const int UPS = 5;

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
    bool is_human = false;

    public:
    View& view;
    std::list<Rabbit> rabbits;
    std::list<Snake> snakes;
    std::vector<std::vector<char>> field; 

    Model(View& view_, int num_of_bots_ = 2, int num_of_rabbits_ = 5, bool is_human_ = false)
    : view(view_), field(151, std::vector<char>(91))///////////////////////////////////////////
    {
        num_of_bots = num_of_bots_;
        num_of_rabbits = num_of_rabbits_;
        is_human = is_human_;

        generate_rabbits();
        generate_snakes();
        auto f = std::bind(&Model::update, this);
        view.set_ontimes(f);
    }

    void set_name(char* buff);
    void update();

    void set_field();
};

enum direction
{
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
};
