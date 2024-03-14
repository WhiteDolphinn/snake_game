#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
//#include "game.hpp"

using coord = std::pair<int, int>;


class Snake
{
    private:
    int length;
    coord head;
    coord tail;
    std::list<coord> body;

    public:
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
    static View* view;
    static View* get(std::string s = "text");
    virtual ~View();
    virtual void print_game_name(std::string game_name) = 0;
    virtual void draw() = 0;
    virtual void draw(std::list<Rabbit>& rabbits) = 0;
};
