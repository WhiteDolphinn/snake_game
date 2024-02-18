#pragma once
#include <iostream>
#include "game.hpp"

class Control
{
    private:

    Model& model;

    public:

    Control(Model& model_)
        : model(model_)
    {
    }

    void get_user_input();
};
