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
