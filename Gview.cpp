#include "Gview.hpp"
#include "game.hpp"
//#include <unistd.h>

const int BUFSIZE = 10;

GView::GView()
        : window(sf::VideoMode(win_size.first*pixel_size, win_size.second*pixel_size), "Game: Snake"), brick(sf::Vector2f(10.f, 10.f))
{
    brick.setFillColor(sf::Color::Green);
    brick.setPosition(win_size.first*pixel_size/2, win_size.second*pixel_size/2);

    if(!rabbit_texture.loadFromFile("krolik4.png"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    rabbit.setTexture(rabbit_texture);

    
    if(!snake_body_texture.loadFromFile("snakebody.jpg"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    snake_body.setTexture(snake_body_texture);

    if(!snake_head_texture.loadFromFile("snakehead.jpg"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    snake_head.setTexture(snake_head_texture);


    //rabbit.set

    window.setFramerateLimit(frame);   
}

GView::~GView()
{
    
}

void GView::draw()
{

    for(int i = 0; i < win_size.first; i++)
    {
        brick.setPosition(i*pixel_size, 0);
        window.draw(brick);
        brick.setPosition(i*pixel_size, win_size.second*pixel_size-pixel_size);
        window.draw(brick);
    }

    for(int i = 0; i < win_size.second; i++)
    {
        brick.setPosition(0, i*pixel_size);
        window.draw(brick);
        brick.setPosition(win_size.first*pixel_size-pixel_size, i*pixel_size);
        window.draw(brick);
    }


}

void GView::draw(std::list<Rabbit>& rabbits, std::list<Snake>& snakes)
{
    draw();

    for(const auto& rabbit: rabbits)
        draw_rabbit(rabbit);

    for(const auto& snake: snakes)
        draw_snake(snake);

    return;
}

void GView::draw_rabbit(const Rabbit& rabbit_)
{
    rabbit.setPosition(rabbit_.xy.first*pixel_size, rabbit_.xy.second*pixel_size);
    window.draw(rabbit);
}

void GView::draw_snake(const Snake& snake)
{
    snake_head.setPosition(snake.head.first*pixel_size, snake.head.second*pixel_size);
    window.draw(snake_head);

    for(const auto& part: snake.body)
    {
        snake_body.setPosition(part.first*pixel_size, part.second*pixel_size);
        window.draw(snake_body);
    }
    
    snake_body.setPosition(snake.tail.first*pixel_size, snake.tail.second*pixel_size);
    window.draw(snake_body);

    return;
}

void GView::print_game_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl;
}

void GView::bye_print()
{
    return;
}

void GView::mainloop()
{
    int direction = 0;
    int frame_number = 0;

    while (window.isOpen())
    {
        rabbit.setPosition(100, 100);
        window.draw(rabbit);

        frame_number = (frame_number + 1) % frame;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();
        if(frame_number % (frame/5) != 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                direction = UP;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                direction = DOWN;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                direction = LEFT;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                direction = RIGHT;

            for(const auto& onkey: onkeys)
                onkey(direction);

            draw_without_update();
        }
        else
        {
            for(const auto& ontime: ontimes)
                ontime();
        }
            window.display();

    }

    return;
}
