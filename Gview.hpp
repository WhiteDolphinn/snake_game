#pragma once
#include "view.hpp"

class GView : public View
{
    public:
    virtual void print_game_name(std::string game_name);
    virtual void draw();
    virtual void draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes);
    virtual void bye_print();
    virtual void mainloop();
    //virtual ~GView();
};
