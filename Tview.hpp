#pragma once
#include "view.hpp"

class TView : public View
{
    private:
    void cls();
    void setcolor(int brightness, int color);
    void gotoxy(int x, int y);
    void draw_wall(char symbol, int start_x, int start_y, int end_x, int end_y);

    public:
    virtual void print_game_name(std::string game_name);
    virtual void draw();
};
