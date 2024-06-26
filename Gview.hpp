#pragma once
#include "view.hpp"
#include <SFML/Graphics.hpp>

const int pixel_size = 10;

class GView : public View
{
    private:
    sf::RenderWindow window;
    sf::RectangleShape brick;

    sf::Sprite rabbit;
    sf::Texture rabbit_texture;

    sf::Sprite snake_body;
    sf::Sprite snake_body_human;
    sf::Sprite snake_body_stupid_bot;
    sf::Sprite snake_body_smart_bot;
    sf::Texture snake_body_texture_human;
    sf::Texture snake_body_texture_stupid_bot;
    sf::Texture snake_body_texture_smart_bot;

    sf::Sprite snake_head;
    sf::Texture snake_head_texture;

    sf::Text text_box;
    sf::Font font;

    unsigned frame = 200;

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
