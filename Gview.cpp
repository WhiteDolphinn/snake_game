#include "Gview.hpp"
#include "game.hpp"
//#include <unistd.h>

const int BUFSIZE = 10;

GView::GView()
        : window(sf::VideoMode(1600, 800), "Game: Snake"), brick(sf::Vector2f(10.f, 10.f))
{
    brick.setFillColor(sf::Color::Green);
    brick.setPosition(800.f, 400.f);
    window.setFramerateLimit(2);   
}

GView::~GView()
{
    
}

void GView::draw()
{

    for(int i = 0; i < 1600/pixel_size; i++)
    {
        brick.setPosition(i*pixel_size, 0);
        window.draw(brick);
        brick.setPosition(i*pixel_size, 800-pixel_size);
        window.draw(brick);
    }

        for(int i = 0; i < 800/pixel_size; i++)
    {
        brick.setPosition(0, i*pixel_size);
        window.draw(brick);
        brick.setPosition(1600-pixel_size, i*pixel_size);
        window.draw(brick);
    }


}

void GView::draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes)
{
    //usleep(100000);
    draw();

    for(const auto& rabbit: rabbits)
        draw_rabbit(rabbit);

    for(const auto& snake: snakes)
        draw_snake(snake);

    return;
}

void GView::draw_rabbit(const Rabbit& rabbit)
{
    brick.setPosition(rabbit.xy.first*10, rabbit.xy.second*10);
    window.draw(brick);
}

void GView::draw_snake(const Snake& snake)
{
    brick.setPosition(snake.head.first*10, snake.head.second*10);
    window.draw(brick);

    for(const auto& part: snake.body)
    {
        brick.setPosition(part.first*10, part.second*10);
        window.draw(brick);
    }
    
    brick.setPosition(snake.tail.first*10, snake.tail.second*10);
    window.draw(brick);

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

void GView::mainloop()
{
    int direction = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction = UP;
            for(const auto& onkey: onkeys)
            {
                onkey(direction);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction = DOWN;
            for(const auto& onkey: onkeys)
            {
                onkey(direction);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction = LEFT;
            for(const auto& onkey: onkeys)
            {
                onkey(direction);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction = RIGHT;
            for(const auto& onkey: onkeys)
            {
                onkey(direction);
            }
        }

        for(const auto& ontime: ontimes)
        {  
            ontime();
        }
        
        window.display();

    }

    

    return;
}
