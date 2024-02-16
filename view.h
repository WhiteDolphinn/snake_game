#pragma once
#include <iostream>
#include <string>

class View
{
    public:
    static View* view;
    static View* get(std::string s = "text");
    virtual ~View();
    virtual void print_game_name(std::string game_name) = 0;
    virtual void draw() = 0;
};

class TView : public View
{
    private:
    void cls();
    void setcolor(int brightness, int color);
    void gotoxy(int x, int y);

    public:
    virtual void print_game_name(std::string game_name);
    virtual void draw();
};

class GView : public View
{
    public:
    virtual void print_game_name(std::string game_name);
    virtual void draw();
};
