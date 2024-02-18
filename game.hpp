#pragma once
#include <string.h>
#include "view.hpp"

const int length_game_name = 15;

class Model
{
    private:
    View& view;
    char game_name[length_game_name] = {};

    public:

    Model(View& view_)
    : view(view_)
    {
    }

    void set_name(char* buff);
};
