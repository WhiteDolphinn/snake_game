#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
//#include "game.hpp"

using coord = std::pair<int, int>;


class Snake
{
    public:
    int length;
    coord head;
    coord tail;
    std::list<coord> body;
};

class Rabbit
{
    private:
    public:
    coord xy;
};

class View
{
    public:
    coord win_size = {0, 0};
    static View* view;
    static View* get(std::string s = "text");
    View();
    virtual ~View();
    virtual void print_game_name(std::string game_name) = 0;
    virtual void draw() = 0;
    virtual void draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes) = 0;
    virtual void bye_print() = 0;
};
