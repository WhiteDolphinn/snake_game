#pragma once
#include <iostream>
#include "game.h"

class Control
{
    private:

    Model& model;

    public:

    Control(Model& model_)
        : model(model_)
    {

    }

    void get_user_input()
    {
        char buff[length_game_name] = {};
        std::cin >> buff;
        model.set_name(buff);
    }
};
