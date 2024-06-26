#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <termios.h> 
#include <functional> 
#include <cstdlib>  
//#include "game.hpp"

using keyfn = std::function<void(int)>;
using timefn = std::function<void()>;
using drawfn = std::function<void()>;

//using coord = std::pair<int, int>;

struct coord: public std::pair<int, int>
{
    using base = std::pair<int, int>;
    using base::base;

    int dist(const coord& c)
    {

        return std::abs(c.first - first) + std::abs(c.second - second);
    }
};

class Snake
{
    public:
    int length;
    int last_length = 0;
    int direction = 1;
    bool is_controlled = false;
    bool is_stupid_bot = false;
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
    protected:
    struct termios old_term;
    public:
    bool is_game_goes = true;
    coord win_size = {0, 0};
    static View* view;
    static View* get(std::string s = "text");
    View();
    virtual ~View();
    virtual void print_game_name(std::string game_name) = 0;
    virtual void draw() = 0;
    virtual void draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes) = 0;
    virtual void bye_print() = 0;

    virtual void draw_rabbit(const Rabbit& rabbit) = 0;
    virtual void draw_snake(const Snake& snake) = 0;

    virtual void mainloop() = 0;

    void set_onkey(keyfn f);
    void set_ontimes(timefn f);
    void set_draw_without_update(drawfn f);

    std::list<keyfn> onkeys;
    std::list<timefn> ontimes;
    drawfn draw_without_update;
};
