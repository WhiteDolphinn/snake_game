#pragma once
#include <iostream>
#include "game.hpp"

class Control
{
    private:
    Model& model;
    Snake& snake;


    public:

    Control(Model& model_, Snake& snake_);
    void get_user_input();
    void key_pressed(int key);
    void timer();

};
