#include "Gview.hpp"
#include "game.hpp"
//#include <unistd.h>

const int BUFSIZE = 10;

GView::GView()
        : window(sf::VideoMode(150*pixel_size+300, 90*pixel_size), "Game: Snake"), brick(sf::Vector2f(10.f, 10.f))
{
    win_size.first = 150;
    win_size.second = 90;
    brick.setFillColor(sf::Color::Green);
    brick.setPosition(win_size.first*pixel_size/2, win_size.second*pixel_size/2);

    if(!rabbit_texture.loadFromFile("krolik4.png"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    rabbit.setTexture(rabbit_texture);

    
    if(!snake_body_texture.loadFromFile("snakebody.jpg"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    snake_body.setTexture(snake_body_texture);

    if(!snake_head_texture.loadFromFile("snakehead2.png"))
        std::cout<< "povialdjvldfbjkdf[p;bljkvp[;lgx;kbd;bvd;l]]" << std::endl;
    snake_head.setTexture(snake_head_texture);

    text_box.setCharacterSize(24);
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "zhopa" << std::endl;
    }
    text_box.setFont(font);
    text_box.setFillColor(sf::Color::Red);
    text_box.setPosition(win_size.first*pixel_size + 2*pixel_size, 3*pixel_size);

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

    
    text_box.setPosition(win_size.first*pixel_size + 2*pixel_size, 3*pixel_size);
    int snake_number = 0;
    for(const auto& snake: snakes)
    {
        if(snake.head == coord{0, 0} || snake.length == 0)
            text_box.setFillColor(sf::Color::Red);
        else
            text_box.setFillColor(sf::Color::Green);

        if(snake.is_controlled == true)
            text_box.setString("snake(human)"+ std::to_string(snake_number)+ ": " + std::to_string(snake.length + snake.last_length));
        else
            text_box.setString("snake(bot)"+ std::to_string(snake_number)+ ": " + std::to_string(snake.length + snake.last_length));
        window.draw(text_box);
        text_box.move(0, 3*pixel_size);
        snake_number++;
    }


    std::string str = "";
    snake_number = 0;

    for(const auto& snake: snakes)
    {
        if(snake.is_controlled == true)
            str += "snake(human)"+ std::to_string(snake_number++)+ ": " + std::to_string(snake.last_length + snake.length) + "\n";
        else
            str += "snake(bot)"+ std::to_string(snake_number++)+ ": " + std::to_string(snake.last_length + snake.length) + "\n";
    }
    text_box.setString(str);

    return;
}

void GView::draw_rabbit(const Rabbit& rabbit_)
{
    rabbit.setPosition((rabbit_.xy.first-1)*pixel_size, (rabbit_.xy.second-1)*pixel_size);
    window.draw(rabbit);
}

void GView::draw_snake(const Snake& snake)
{
    snake_head.setPosition((snake.head.first-1)*pixel_size, (snake.head.second-1)*pixel_size);

    if(snake.direction == RIGHT)
    {
        snake_head.setRotation(-90.f);
        snake_head.move(0, pixel_size);
    }
    if(snake.direction == LEFT)
    {
        snake_head.setRotation(90.f);
        snake_head.move(pixel_size, 0);
    }
    if(snake.direction == DOWN)
    {
        snake_head.setRotation(180.f);
        snake_head.move(pixel_size, pixel_size);
    }

    window.draw(snake_head);
    snake_head.setRotation(0);

    for(const auto& part: snake.body)
    {
        snake_body.setPosition((part.first-1)*pixel_size, (part.second-1)*pixel_size);
        window.draw(snake_body);
    }
    
    snake_body.setPosition((snake.tail.first-1)*pixel_size, (snake.tail.second-1)*pixel_size);
    window.draw(snake_body);

    return;
}

void GView::print_game_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl;
}

void GView::bye_print()
{
    text_box.setPosition(win_size.first*pixel_size/2 - 150, 2*pixel_size);
    std::string str = text_box.getString();
    text_box.setString(str);

    window.draw(text_box);
    return;
}

void GView::mainloop()
{
    int direction = 0;
    int frame_number = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if(is_game_goes == false && (frame_number % (frame/5) == 0))
        {
            bye_print();
            window.display();
            continue;
        }

        frame_number = (frame_number + 1) % frame;


        window.clear();
        if(frame_number % (frame/5) != 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != DOWN)
                direction = UP;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != UP)
                direction = DOWN;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != RIGHT)
                direction = LEFT;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != LEFT)
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
