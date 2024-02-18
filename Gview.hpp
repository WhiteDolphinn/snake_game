#pragma once
#include "view.hpp"

class GView : public View
{
    public:
    virtual void print_game_name(std::string game_name);
    virtual void draw();
};
