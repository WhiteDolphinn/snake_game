#pragma once
#include <string.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "view.hpp"

const int length_game_name = 15;
const int num_of_rabbits = 5;


class Model
{
    private:
    View& view;
    char game_name[length_game_name] = {};

    std::list<Rabbit> rabbits;
    std::list<Snake> snakes;

    public:

    Model(View& view_)
    : view(view_)
    {
        srand(time(NULL));
        Rabbit rabbit;

        for(int i = 0; i < num_of_rabbits; i++)
        {   
            /*rabbit.xy.first = 10;
            rabbit.xy.second = 10;*/
            rabbit.xy.first = rand() % 20;
            rabbit.xy.second = rand() % 20;
            rabbits.push_back(rabbit);
        }
    }

    void set_name(char* buff);
};
