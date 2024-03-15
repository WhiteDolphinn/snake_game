#include "Gview.hpp"

void GView::draw()
{

    print_game_name("grsnake");
}

void GView::draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes)
{
    return;
}

void GView::print_game_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}

void GView::bye_print()
{
    return;
}