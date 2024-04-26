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
    void draw_without_update();

    void stupid_bot();
    void smart_bot();
    coord next_generation(std::vector<coord>& generation);
    bool in_bounds(int len1, int len2);

};

class Cell
{
    public:
    coord cell;

    Cell* left = nullptr;
    Cell* right = nullptr;
    Cell* up = nullptr;
    Cell* down = nullptr;

    Cell(coord cell_)
    {
        cell = cell_;
    };
};
