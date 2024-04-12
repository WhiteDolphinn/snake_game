#pragma once
#include "view.hpp"
#include <SFML/Graphics.hpp>

const int pixel_size = 10;

class GView : public View
{
    private:
    sf::RenderWindow window;
    sf::RectangleShape brick;

    public:
    GView();
    ~GView();
    virtual void print_game_name(std::string game_name);
    virtual void draw();
    virtual void draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes);
    virtual void bye_print();
    virtual void mainloop();

    void draw_rabbit(const Rabbit& rabbit);
    void draw_snake(const Snake& snake);
    //virtual ~GView();
};
