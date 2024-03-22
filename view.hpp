#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <termios.h> 
#include <functional>   
//#include "game.hpp"

using coord = std::pair<int, int>;
using keyfn = std::function<void(int)>;


class Snake
{
    public:
    int length;
    int direction = 1;
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
    private:
    struct termios old_term;
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

    void mainloop();
    void set_onkey(keyfn f);
    std::list<keyfn> onkeys;
};
