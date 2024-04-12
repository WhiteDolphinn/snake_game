#pragma once
#include "view.hpp"
#include "game.hpp"


class TView : public View
{
    private:
    void cls();
    void setcolor(int brightness, int color);
    void gotoxy(int x, int y);
    void draw_wall(char symbol, int start_x, int start_y, int end_x, int end_y);
    void draw_rabbit(const Rabbit& rabbit);
    void draw_snake(const Snake& snake);

    public:
    TView();
    ~TView();
    virtual void print_game_name(std::string game_name);
    virtual void draw();
    virtual void draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes);
    virtual void bye_print();
    virtual void mainloop();
    //virtual ~TView();
};
